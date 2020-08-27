#ifndef __WINDOWS_H_
#define __WINDOWS_H_

#ifdef _MSC_VER
#define __MSVC__
#endif

typedef DWORD unsigned long;
typedef PDWORD DWORD*;
typedef WINAPI __stdcall;
typedef LPCSTR char*;
typedef HANDLE int;
typedef PHANDLE HANDLE*;
typedef SOCKET int;



#endif /* _WINDOWS_H_ */
