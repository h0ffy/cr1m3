#ifndef __HTTP_H_FILE
#define __HTTP_H_FILE


#define HTTP_RETURN "\r\n\r\n"

#define MAX_GET_LEN 1024


HINTERNET __http_connect(char *get);
int __http_make_get(char *get_data, char *option, char *data, char *token);
int __http_reply(char *get_data, char *reply);
int __http_read(char *get_data, char *reply);
int __http_close(HINTERNET hRequest);


#endif /* __HTTP_H_FILE */
