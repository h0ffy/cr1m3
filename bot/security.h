#ifndef __HTTP_H_FILE
#define __HTTP_H_FILE

/* ROL/ROR macro */
#define __ror(val,key) \
    __asm__ ( \
            "rorq %b1,%q0"\
            :"+g" (val) \
            :"Jc" (key) )

#define __rol(val,key) \
    __asm__ ( \
            "rolq %b1,%q0"\
            :"+g" (val) \
            :"Jc" (key) )

#define __xor(val,key) \
    __asm__ ( \
            "xorq %b1,%q0"\
            :"+g" (val) \
            :"Jc" (key) )



int __security_anti_debug(void);

#endif
