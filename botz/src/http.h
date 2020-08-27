#ifndef __HTTP_H_FILE
#define __HTTP_H_FILE

#define METHOD "GET\0"
//#define MSG_FORMAT "/cc.php?bid=%s&option=%d&data=%s&token=%s"
#define LOGIN_FORMAT "%s###%s###%s###%s"
#define MSG_FORMAT "/rpc.php?bid=%s&option=%d&data=%s&token=%s"
#define VAR_BID "?bid=\0"
#define VAR_OPTION "&option=\0"
#define VAR_DATA "&data=\0"
#define VAR_TOKEN "&token=\0"

int __http_close(void *hRequest);
int __http_read(char *get_data, char *reply);
int __http_reply(char *get_data, char *reply);

int __http_make_get(char *get_data, char *option, char *data, char *token);
void * __http_connect(char *get);


void * __hxxp_connect();
int __hxxp_login(void);
int __hxxp_request(int option, char *data, char *token);
int __hxxp_reply(char *reply);
int __hxxp_close();
#endif