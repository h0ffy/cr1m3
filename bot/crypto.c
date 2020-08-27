

int __xor(char *data, unsigned short key) {
#if defined(_MSC_VER)
	__asm {
		lea eax, data
		lea ebx, key
		xor eax, ebx
	}

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




