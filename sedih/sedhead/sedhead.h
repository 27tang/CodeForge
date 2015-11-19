/*
    stuff i use for stuff.


    I really want to know how i should handle increments in for loops in 
    my macros.
        Have them pass an increment variable?
                         ||
        Have the mixed declaration and declare it with random __'s.
*/

#ifndef _SED_HEAD_
#define _SED_HEAD_
#include <sys/types.h>
#include <stdio.h>                  
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

/*#define NDEBUG*/
#include <assert.h>


#ifdef __SED_ERR__
    #include "err_handle/err_handle.h"  /* error handling functions */
#endif
#ifdef __SED_NUM__
    #include "get_num/get_num.h"        /* convert strings to int types */
#endif

#ifdef __SED_LINUX__
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/time.h>

    /* allocate an input buffer with a '\0' terminatior at the end */
    #define allocInputBuff(buff)                                               \
    {                                                                          \
        ssize_t _retBytes = 0;                                                 \
        if((_retBytes = read(fd, (void*) buff, IN_BUF_-1)) == -1){             \
            errExit("alloc_buf(): read() failure");}                           \
        (_retBytes < IN_BUF_-1) ? (buff[_retBytes] = '\0')                     \
                                : (buff[IN_BUF_-1] = '\0');                    \
    } 

    /* reset the input buffer after first allocation */
    #define setInputBuf(buff, bfPl)                                            \
    {                                                                          \
        alloc_buff(buff);                                                      \
        bfPl = buff;                                                           \
    } 

#endif


#ifndef __FL_CONSTS__
#define __FL_CONSTS__
/* Use memcpy to set a float value, causing the proper value to appear instead
   of the min/max. (example: Nan, -Nan, etc.), (memset gives improper results) */
#define set_float(num, set)    memcpy(&num, &set, sizeof(num))
#define set_double(num, set)   set_float(num,set)
#define set_nan(num, set)      set_float(num, set)
#define set_inf(num, set)      set_float(num,set)

/* Use these definitions placed in memory for the above macros in set.
   example: int32_t fnan = PF_NAN;
            int64_t dnegInf = ND_INF;

            set_float(num, fnan);
            set_double(num, dneginf); */

/* 32 bit float */
#define PF_NAN  0x7fc00000    /* positive NAN */
#define NF_NAN  0xffc00000    /* negetive NAN */

#define PF_INF  0x7f800000    /* positive INF */
#define NF_INF  0xff800000    /* negetive INF */

/* 64 bit double */
#define PD_NAN  0x7ff8000000000000    /* positive NAN */
#define ND_NAN  0xfff8000000000000    /* negetive NAN */

#define PD_INF  0x7ff0000000000000    /* positive INF */
#define ND_INF  0xfff0000000000000    /* negetive INF */
#endif 

                    /* __restrict */
#ifndef Restrict
#define Restrict __restrict
#endif

                    /* bool */
#ifdef true 
#undef true
#endif
#ifdef false 
#undef false 
#endif
typedef enum {false, true} Bool;

                    /* min/max */
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

                    /* input */
/* clears the input buffer using variable char ch; and getchar (). */
#define clear_buff(ch) while(((ch) = getchar()) != '\n' && (ch) != EOF)

/* get 1 character from stdin using getchar, clear buffer afterwards if
   needed */
#define getChar(input)                \
{                                     \
    char _c_h_ = '\0';                \
    if(((input) = getchar()) != '\n'){\
        clear_buff(_c_h_);}           \
} /* end getChar */

/* get a single character from stdin and loop untill input is correct 
   note: sets the single character to a capital letter */
#define yesNo(input, string, ...)                               \
{                                                               \
    do                                                          \
    {                                                           \
        printf((string), __VA_ARGS__);                          \
        getChar((input));                                       \
        (input) = toupper((input));                             \
    }while(input != 'Y' && input != 'N');                       \
} /* end getChar_check #}}} */

/* get a line of input from a buffer, clears the buffer if required. Input
   must be dealloced or on the heap for compilation */
#define getLineInput(input, max, filepntr, len)       \
{                                                     \
    char __c_h__ = '\0';                              \
    if((input) == NULL){                              \
        (input) = (char*) malloc(sizeof(char)*max);}  \
                                                      \
    memset((input), '\0', max);                       \
    fgets((input),(max),(filepntr));           \
    (len) = strlen((input)) - 1;               \
    if(input[(len)] == '\n'){                  \
        input[(len)] = '\0';}                  \
    else{                                      \
        clear_buff(__c_h__); }                 \
} /* end getLineInput */

                    /* other */
/* Copy a variable ammount of characters from a buffer based on a given position
   and place in resStr based on a conditional. Terminating the resStr with a '\0'
   value.  */
#define getBufString(inBuf, bfPl, resStr, conditional)                         \
{                                                                              \
    int _TM_ = 0;                                                              \
    for(_TM_ = 0; conditional; ++_TM_)                                         \
    {                                                                          \
        resStr[_TM_] = *bfPl;                                                  \
        ++bfPl;                  /* increase buff placement */                 \
        if(*bfPl == '\0'){ /* reached end of current buffer */                 \
            setBuf(inBuf, bfPl);}                                              \
    } /* end for */                                                            \
    ++bfPl;                                                                    \
    resStr[_TM_] = '\0';                                                       \
    if(*bfPl == '\0'){ /* reached end of current buffer */                     \
        setBuf(inBuf, bfPl);}                                                  \
} 

/* create a bit mask for a given range of bits. start, end. (lsb,msb) */
#define create_mask(increment, start, end, resMask)                         \
{                                                                           \
    if((start) > (end)){                                                    \
        errmsg("create_mask: start > end, no mask was generated.");}        \
                                                                            \
    resMask = 0; /* just to make sure im not an idiot when i call this */   \
    for((increment) = (start); i <= (end); ++(increment)){                  \
        (resMask) |= 1 << increment;}                                       \
} /* end create_mask */

/* adds all the ascii values in a character array together */
#define sumChars(increment, array, size, res)                 \
{                                                             \
    for((increment) = 0; (increment) < (size), ++(increment)){\
        (res) += (array[(increment)]);}                       \
} /* end sumChars */

/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS could be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define apply_funct(type, funct, ...)                      \
{                                                          \
    void *stopper = (int[]){0};                            \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};   \
    int __i_;                                              \
                                                           \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){    \
        (funct)(apply_list[__i_]);}                        \
} /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define free_all(...)   apply_funct(void, free, __VA_ARGS__)
#endif
