/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef H_RTHREADS
#define H_RTHREADS

#ifdef __cplusplus
#define extern "C" {
#endif
		

	void __stdcall __rthreads_procMigrate(void *params);
	void __stdcall __rthreads_test(void *params);
	void __stdcall __rthreads_load_dll(void *params);




#ifdef __cplusplus
}
#endif
#endif
