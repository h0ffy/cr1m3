#ifndef __PROC_H_FILE
#define __PROC_H_FILE


/* OTHER PROCESS CONTROL */
int __set_privileges(HANDLE hProcess,HANDLE hThread);
int __get_one_thread_from_process(int pid);


/* PROCESS CONTROL */
HANDLE __open_process(int pid);


/* THREAD CONTROL */
HANDLE __open_thread(int tid);



/* LIST PROCESS */
int __get_process_by_name(char *process_name, int option);


#endif
