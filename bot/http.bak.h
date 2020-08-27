#ifndef __HTTP_H_FILE
#define __HTTP_H_FILE


#define HTTP_RETURN "\r\n\r\n"

HINTERNET __http_connect();
int __http_make_reply(char *post_data, int post_data_len, char *option, char *data, char *token);
int __http_reply(HINTERNET hRequest, char *post_data, char *reply);
int __http_read(HINTERNET hRequest, char *reply);
int __http_make_contentlength(char *header, unsigned int max_len, unsigned int content_length);
int __http_close(HINTERNET hRequest);


#endif /* __HTTP_H_FILE */
