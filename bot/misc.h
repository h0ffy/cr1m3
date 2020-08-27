#ifndef __MISC_H_FILE
#define __MISC_H_FILE



char *__strtok(char *s, const char *delim);
int __get_end_of_line(const char *buff);
int __get_last_char(const char *buff, char delimiter);
char * __get_last_char_pointer(char *buff, char delimiter);
int __trim(unsigned char *buff);
int __realign_array_left(char *buff);


int __memcpy(unsigned char *dst, unsigned char *src, int max);
int __strncpy(char *dst, char *src, int max);
int __strcpy(char *dst, char *src);
int __strlen(char *buff);

#endif /* __MISC_H_FILE */
