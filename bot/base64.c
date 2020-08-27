#include <windows.h>
#include <stdio.h>
#include <wincrypt.h>
#include "config.h"
#include "base64.h"


extern int os_version; 


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
	
	if(os_version>1) {
		status = CryptBinaryToStringA((const BYTE *)original, original_len, CRYPT_STRING_BASE64|CRYPT_STRING_NOCRLF, encoded, &len);
		if(status==FALSE && lstrlenA(encoded))
			status=TRUE;

		return(status);
	}

	else {
		if(CryptBinaryToStringA((const BYTE *)original, original_len, CRYPT_STRING_BASE64, encoded, &len)==TRUE) {
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
	if(CryptStringToBinaryA(original, original_len, CRYPT_STRING_BASE64, (BYTE *)decoded, &len, 0, &flags)==TRUE)
		return(1);
	

	return(0);

}



