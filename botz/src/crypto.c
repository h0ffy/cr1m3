/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/


#include "crypto.h"
// no found bad thinking no more weed inna programming time
int __xor(char *data,unsigned short key) {
#if defined(_MSC_VER)
	#ifdef _WIN64
		__asm {
				lea rax, data
				lea rbx, key
				xor rax, rbx
		}
	#else
        __asm {
                lea eax, data
                lea ebx, key
                xor eax, ebx
        }
	#endif
#else
        __asm("mov $data, %eax");
        __asm("mov $key, %eax");
        __asm("xor %ebx, %eax");
#endif
        return 0;
}

int __double_xor(char *data, unsigned short key1, unsigned short key2) {
        __xor(data, key1);
        __xor(data, key2);
        return 0;
}

