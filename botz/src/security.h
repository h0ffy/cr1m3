/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef __SECURITY_H_FILE
#define __SECURITY_H_FILE




int __security(void);


int __stdcall __security_monitor(void *params);
int __stdcall __unkill_control(unsigned long dwCtrlType);


//FUNCTIONS
int __security_process(void);
int __security_unkill(void);

#endif
