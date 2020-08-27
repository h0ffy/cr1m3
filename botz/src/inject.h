#ifndef __INJECT_H_FILE
#define __INJECT_H_FILE

int __inject_thread(void *thread_addr, void *arguments,int arguments_len, int pid, int is_exit);
int __inject_migration(int pid, void *arguments);
int __inject_dll(int pid, const char *dll);

//Threads Procs
//void __stdcall procTest(void *params);


#endif
