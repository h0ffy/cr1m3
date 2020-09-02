/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef __TASK_REPLY_H_FILE
#define __TASK_REPLY_H_FILE


#define MAX_TASK_REPLY 90000
#define STATUS_WRITTEN 1
#define STATUS_READED 0


#define OPTION_REGISTER 0x01
#define OPTION_BOTSHELL 0x02
#define OPTION_PROCESS 0x03
#define OPTION_UPLOAD 0x04
#define OPTION_KEYLOGGER 0x05
#define OPTION_SCREENSHOT 0x06

typedef struct _TASK_REPLY {
	char *buff;
	char *token;
	int buff_len;
	unsigned int opt;
	int status;
} TASK_REPLY;

int __push_reply(char *reply,int option);
int __pop_reply(char *reply);
//int __del_reply();

#endif
