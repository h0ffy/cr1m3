#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#include "info.h"

char *os_info[] = {"Windows NT", "Windows XP/2003", "Windows Vista", "Windows 7/2008", "Windows 8/2012", "Windows 8.1" };
char *arch_info[] = {" 32bits", " 64bits"};

int os_version = 0;


/*
 * @brief Get information about system and hardware
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_info(info *s_info) {

	//get volume serial
	if(__get_volume_serial(s_info)!=1)
		return 0xFFFFFFFF;
	
	if(__get_user_name(s_info)==0)
		return 0xFFFFFFFF;

	if(__get_computer_name(s_info)==0)
		return 0xFFFFFFFF;

	if(__get_computer_name(s_info)==0)
		return 0xFFFFFFFF;

	return 0;
}

//no include in free version ¬¬ (leak !)
int __get_volume_serial(info *s_info) {
	char *sys_drive = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 1024);
	unsigned long serial;
	unsigned short serial_high,serial_low;

	HLOCAL final = LocalAlloc(LHND, 1024);
	


	if(GetSystemDirectoryA(sys_drive, 128)!=0) {
		sys_drive[3]=0x00;
		if(GetVolumeInformationA(sys_drive, NULL, NULL, &serial, NULL, NULL, NULL,NULL)==FALSE) {
			serial=0;
		}
	}

	else {
		serial = 0;
	}

	sys_drive[3]='J'; //mark :) The real h4x0r fuckin' this line

	if(sys_drive) {
		ZeroMemory(sys_drive, 1024);
		HeapFree(sys_drive, HEAP_NO_SERIALIZE, NULL);
	}


	serial_high = HIWORD(serial);
	serial_low = LOWORD(serial);
	StringCbPrintfA(s_info->volume_serial,128,"%X-%X", serial_high, serial_low);
	
	if(final)
		LocalFree(final);

	return TRUE;

}

int __get_user_name(info *s_info) {
	DWORD tmp;
	return(GetUserNameA(s_info->user_name, &tmp));

}

int __get_computer_name(info *s_info) {
	DWORD tmp;
	return(GetComputerNameExA((COMPUTER_NAME_FORMAT)6,s_info->computer_name, &tmp));
}


int __get_windows_version(info *s_info) {
	OSVERSIONINFOA os_ver = {0};
	int arch=0;
	
	

	os_ver.dwOSVersionInfoSize = sizeof(os_ver);
	if(GetVersionExA(&os_ver)) {
		if(!(os_ver.dwPlatformId == VER_PLATFORM_WIN32_NT))
                        os_version = 0;
		else if(os_ver.dwMajorVersion == 5)
                    os_version = 1;
        else if(os_ver.dwMajorVersion == 6 && os_ver.dwMinorVersion == 0)
                os_version = 2;
        else if(os_ver.dwMajorVersion == 6 && os_ver.dwMinorVersion == 1)
                os_version = 3;
        else if(os_ver.dwMajorVersion == 6 && os_ver.dwMinorVersion == 2)
                os_version = 4;
        else
                os_version = 5;
    }

    if(sizeof(void *)==4)
            arch=0;
    else
            arch=1;


	lstrcpynA(s_info->os_version, os_info[os_version], lstrlenA(os_info[os_version]));
	lstrcatA(s_info->os_version, arch_info[arch], lstrlenA(arch_info[arch]));


	return(1);
}




