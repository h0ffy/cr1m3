#include <stdio.h>


extern int _compute_hash(char *buff);
//extern int _resolve_api_hash(char *api_name, int key);

int main(int argc, char *argv[]) {
	char *buff = "LoadLibraryA";	

	if(argc!=2) {
		printf("%s <api_name>\n", argv[0]);
		return -1;
	}

	printf("%s\t%.8x\n",argv[1], _compute_hash(argv[1]));
//	printf("%.8x\n", _resolve_api_hash("LoadLibraryA", 0x4a));

	return 0;
}
