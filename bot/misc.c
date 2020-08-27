//funciones genericas
#include <windows.h>
#include "misc.h"
#include "config.h"




int __strlen(char *buff) {
	int i=0;
	while(buff[i]!=0)
		i++;

	return(i);
}


int __strcpy(char *dst, char *src) {
	int i = 0;

	while(src[i]!='\0')
		dst[i] = src[i];
	

	return(i);
}


int __strncpy(char *dst, char *src, int max) {
	if(__strlen(src)>max)
		return 0;
	else
		return(__strcpy(dst,src));
}

int __memcpy(unsigned char *dst, unsigned char *src, int max) {
	int i = 0;

	for(i=0;i<max;i++) {
		dst[i]=src[i];
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
	}

	i++;

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

	return(buff+b);
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
// Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
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
