#include <stdio.h>
#define DWORD unsigned int
int rolKey = 13;


unsigned int LDFror(unsigned int X) {
	//return _rotr(X, rolKey);
	return((((X) >> (rolKey % 32)) | ((X) << (32 - (rolKey % 32)))));
}

unsigned int LDFapi_hash(char *c) { // thx. Dan Staples 
	register DWORD ret = 0;
	
	do
	{
		ret = LDFror(ret);
		ret += *c;
	} while (*++c);

	return ret;
}



int main(int argc, char *argv[]) {
	if(argc!=2) {
		printf("Invalid: %s <string>", argv[0]);
		exit(0);
	}

	printf("Hash: %x\n", (*(*LDFapi_hash(argv[1]))));
}
