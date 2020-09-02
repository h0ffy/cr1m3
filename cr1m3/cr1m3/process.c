#include "windows.h"
#include "api.h"
#include "process.h"
#include "misc.h"


proc_struct procs[65535];
int proc_status=0;


int __process_list() {
	LONG status;
	PVOID buffer;
	PSYSTEM_PROCESS_INFO spi;
	int i =0;
	

	buffer=_VirtualAlloc(NULL,1024*1024,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE); // We need to allocate a large buffer because the process list can be large.
	if(!buffer)
	{
		return 0;
	}

	spi=(PSYSTEM_PROCESS_INFO)buffer;

	status=_NtQuerySystemInformation(SystemProcessInformation,spi,1024*1024,NULL);


	spi=(PSYSTEM_PROCESS_INFO)((LPBYTE)spi+spi->NextEntryOffset);

	while(spi->NextEntryOffset)
	{
		_ZeroMemory(procs[i].process, 160);
		_WideCharToMultiByte(0,0,spi->ImageName.Buffer, spi->ImageName.Length, procs[i].process, 160, NULL,NULL);
		procs[i].procid = (unsigned int)spi->ProcessId;
		procs[i].id = i;
		spi=(PSYSTEM_PROCESS_INFO)((LPBYTE)spi+spi->NextEntryOffset); 
		i++;
	}
	
	proc_status = 1;
	_VirtualFree(buffer,0,MEM_RELEASE);
	return 1;
	

	

}


int __get_process(pproc_struct pproc,int id) {
	if(proc_status==0) 
		return 0;

	if(id>=65535)
		return 0;

	if(procs[id+1].id==0)
		return 0;
	
	pproc->id = procs[id].id;
	pproc->procid = procs[id].procid;
	_ZeroMemory(pproc->process, 160);
	_lstrcpynA(pproc->process,procs[id].process,_lstrlenA(procs[id].process)+1);

	return 1;
}



int __kill_process(int pid) {
	void *hProcess = _OpenProcess(0x0001,0x00, pid);

	if(hProcess==0x00)
		return 0;

	_NtTerminateProcess(hProcess, 0x00);
	_CloseHandle(hProcess);

	return 1;
}


int __process_findtoken(unsigned long pid) {
	SYSTEM_HANDLE_INFORMATION *SysHandleInfo;
	DWORD len = 4096, retlen, i, ret, val;
	
	SysHandleInfo = (PSYSTEM_HANDLE_INFORMATION)_HeapAlloc(_GetProcessHeap(), 0, (unsigned long)len);

	while (__getNTSTATUS(_NtQuerySystemInformation(jVX_SystemHandleInformation, SysHandleInfo, len, &retlen)) == (DWORD)0xC0000004) {
		_HeapFree(_GetProcessHeap(), 0, SysHandleInfo);
		len += 4096;
		SysHandleInfo = (PSYSTEM_HANDLE_INFORMATION)_HeapAlloc(_GetProcessHeap(), 0, (unsigned long)len);
	}


	for (i = 0; i <= SysHandleInfo->NumberOfHandles; i++) {
		SYSTEM_HANDLE *pHandle = &(SysHandleInfo->Handles[i]);

		if (pHandle->ObjectTypeNumber == HANDLE_TYPE_TOKEN) {
			#if defined(_MSC_VER)
				__asm { nop }
			#else
				asm("nop");
			#endif
		}

		if (pHandle->ProcessId == pid && pHandle->ObjectTypeNumber == HANDLE_TYPE_TOKEN) {
			return(pHandle->Object);
		}
	}

	_HeapFree(_GetProcessHeap(), 0, SysHandleInfo);

	return 0;
}
