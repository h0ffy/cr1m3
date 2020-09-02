#ifndef __BASE64_H_FILE
#define __BASE64_H_FILE


#ifndef CRYPT_STRING_BASE64_ANY
	#define CRYPT_STRING_BASE64_ANY 0x00000006
#endif

#ifndef CRYPT_STRING_BASE64
	#define CRYPT_STRING_BASE64 0x00000001
#endif

#ifndef CRYPT_STRING_NOCRLF
	#define CRYPT_STRING_NOCRLF 0x40000000
#endif


int __base64_decode(const char *original, const int original_len, unsigned char *decoded);
int __base64_encode(const char *original, const int original_len, char *encoded);
char * __b64_encode(char *val);

#endif /* __BASE64_H_FILE */
