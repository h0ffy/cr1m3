#ifndef H_PE
#define H_PE


int __pe_imp_reconstruct(unsigned long hMemory);

#ifndef __TINYC__
	__declspec(dllexport) void __hook_ExitProcess(DWORD status);
#endif

#endif
