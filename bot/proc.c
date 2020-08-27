#include <Windows.h>
#include <tlhelp32.h>
#include <process.h>

#include <psapi.h>
#include "proc.h"



/****************************************
 *      PROCESS MANIPULATION            *
 ****************************************/
/*
 * @brief Open process
 * @param pid the process id for process open
 * @returns Valid HANDLE process 
 *          0xFFFFFFFF error
 */
HANDLE __open_process(int pid) {
	HANDLE hProcess = NULL;

	

	if((hProcess = OpenProcess(	PROCESS_DUP_HANDLE|PROCESS_VM_OPERATION|
								PROCESS_VM_WRITE|PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,
								FALSE,pid))==0) {

			if((hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid))==0)
				return -1;

	}
	return(hProcess); 
}




/****************************************
 *	THREAD MANIPULATION		*
 ****************************************/
/**
 * @brief Open thread
 * @param tid the thread id for thread open
 * @returns Valid HANDLE process 
 *          0xFFFFFFFF error
 */
HANDLE __open_thread(int tid) {
	HANDLE hThread;
	
	if((hThread = OpenThread(THREAD_GET_CONTEXT|THREAD_SET_CONTEXT|THREAD_SUSPEND_RESUME|SYNCHRONIZE, FALSE, tid))==NULL) {
		return((HANDLE)0xFFFFFF);
	}
	
	
	return(hThread);

}



// sin acabar
int __set_thread_privileges(HANDLE hThread) {
	HANDLE hToken, hDup1, hDup2;
	

	if(OpenThreadToken(hThread, TOKEN_ALL_ACCESS, TRUE, &hToken)==TRUE) {
		if(!DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, TOKEN_IMPERSONATE, TokenImpersonation ,&hDup1)) {
			//add the c0d3
		}
	}	

	return 0;
}


/**
 * @brief Retreive une thread id (not main process) from process 
 * @param pid the process id for list threads of process
 * @returns Valid thread id in process 
 *          0 error
 */
int __get_one_thread_from_process(int pid) {
	THREADENTRY32 thEntry;
	HANDLE hSnap;
	
	if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid))==NULL) {
		return(0);
	}

	if(Thread32First(hSnap, &thEntry)==FALSE) {
		return(0);
	}
	 

	else {
		do {
	                if(thEntry.th32ThreadID != thEntry.th32OwnerProcessID) {
				CloseHandle(hSnap);
        	                return(thEntry.th32ThreadID);
	                }

		} while(Thread32Next(hSnap, &thEntry)==TRUE);


	}
	
	return(0);
}



/****************************************
 *      	PROCESS LIST            *
 ****************************************/
/*
 * @brief Find process or parent pocess from (name)
 * @param process_name string with process name
 * @param option select option process or parent process
 * @returns 0xFFFFFFFF error
 *	    Return valid pid or parent pid if success
 */
int __get_process_by_name(char *process_name, int option) {
	HANDLE hSnap;
	PROCESSENTRY32 thEntry;
	int pid;
	
	

	if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid))==NULL)
		return 0xFFFFFFFF;
	

	if(Process32First(hSnap, &thEntry)==FALSE) {
		CloseHandle(hSnap);
		return 0xFFFFFFFF;
	} 
		

	while(Process32Next(hSnap, &thEntry)!=TRUE) {
			if(lstrcmpA(thEntry.szExeFile,process_name)==0) {
				CloseHandle(hSnap);
				if(option==0)
					return(thEntry.th32ProcessID);
				else
					return(thEntry.th32ParentProcessID);
			}
	}

	CloseHandle(hSnap);
	return 0;

}


