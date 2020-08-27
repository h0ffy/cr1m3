#ifndef __MISC_H_FILE
#define __MISC_H_FILE


#ifdef __TINYC__
	#ifndef __forceinline
		#define __forceinline __inline__
	#endif
#endif


#define IS_ADDRESS_BETWEEN( left, right, address ) ( (address) >= (left) && (address) < (right) )
#define JMP_FUNC(func) __asm { jmp func }
#define RET() __asm { retf }
#define JMP_FUNCRET(func)  JMP_FUNC(func) \
									RET()


char *__strtok(char *s, const char *delim);
int __get_end_of_line(const char *buff);
int __get_last_char(const char *buff, char delimiter);
char * __get_last_char_pointer(char *buff, char delimiter);
int __trim(unsigned char *buff);
int __realign_array_left(char *buff);
int __time_sleep(unsigned int seconds);
int __atoi(char *str);
char* itoa(int value, char* result, int base);


void *__misc_getoffset_ptr(void *base, int offset);
int __misc_getoffset_int(void *base, int offset);
unsigned short __misc_is_wOw64(void);

int __wait_min(int minutes);
int __memcpy(unsigned char *dst, unsigned char *src, int max);
int __strncpy(char *dst, char *src, int max);
int __strcpy(char *dst, char *src);
int __strlen(char *buff);
int __str_is_chr(char *str, char chr);
unsigned long int __getNTSTATUS(unsigned long int val);
char * __alloc(unsigned long len);
void __free(void *mem);
unsigned long __misc_imagebase(void);



/* INIT CODE */
__forceinline void _nop(void) { // no support preffix __ because is intrinsic in C by compilers
#if defined(_MSC_VER)
	__asm { nop }
#else
	__asm("nop");
#endif
}





#endif /* __MISC_H_FILE */
