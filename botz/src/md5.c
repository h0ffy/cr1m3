/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "api.h"
#include "windows.h"
#include "md5.h"

/*
	char md5_str[32] = {0};
	__md5_hash("lala", &md5_str);
	printf("\n%s\n", md5_str);
*/

int __get_md5(char *str, unsigned char *str_md5) {
	unsigned long hCrypt;
	unsigned long hHash;
	unsigned long len;
	unsigned char digits[] = "0123456789abcdef";
	unsigned char md5_val[16] = {0};
	unsigned char tmp[5] = {0};
	unsigned int i = 0;


	_ZeroMemory(str_md5, sizeof(str_md5));
	_ZeroMemory(md5_val, 16);
	

	_CryptAcquireContextA(&hCrypt, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
	_CryptCreateHash(hCrypt, CALG_MD5,0, 0, &hHash);
	_CryptHashData(hHash, str, 4, 0);
	_CryptGetHashParam(hHash, HP_HASHVAL, md5_val, &len, 0);

	
	_ZeroMemory(tmp, 5);

	for(i=0;i<len;i++) {
		//_snprintf(tmp, 2, "%c%c", digits[md5_val[i] >> 4], digits[md5_val[i] & 0xf]);
		tmp[0] = digits[md5_val[i] >> 4];
		tmp[1] = digits[md5_val[i] & 0xf];

		if(i==0)
			_lstrcpyA(str_md5, tmp);
		else 
			_lstrcatA(str_md5, tmp);

	}

	_CryptDestroyHash(hHash);
	_CryptReleaseContext(hCrypt, 0);
	return 0;
}
