#ifndef __INJECT_H_FILE
#define __INJECT_H_FILE

int __inject_thread(void *thread_addr, int pid, int is_exit);
int __inject_migration(int pid);

//Threads Procs
void __stdcall procTest(void *params);


#endif
