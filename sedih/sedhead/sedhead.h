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
    #include "err_handle/err_handle.h"  /* Error handling functions. */
#endif
#ifdef __SED_NUM__
    #include "get_num/get_num.h"        /* Convert strings to int types. */
#endif

#ifdef __SED_LINUX__
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/time.h>

    /* Allocate an input buffer with a '\0' terminatior at the end.
       fd    == int, File descriptor used for allocInputBuff()
       buff  == char*, Buffer to be filled with character data from fd. */
    #define allocInputBuff(fd, buff)                                           \
    {                                                                          \
        ssize_t _retBytes = 0;                                                 \
        if((_retBytes = read(fd, (void*) buff, IN_BUF_-1)) == -1){             \
            errExit("alloc_buf(): read() failure");}                           \
        (_retBytes < IN_BUF_-1) ? (buff[_retBytes] = '\0')                     \
                                : (buff[IN_BUF_-1] = '\0');                    \
    } /* end allocInputBuff */
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
/* clears the input buffer using variable char ch; and getchar ().
   - char ch , throw away character. */
#define clear_buff(ch) while(((ch) = getchar()) != '\n' && (ch) != EOF)

/* Get 1 character from stdin using getchar, clears input buffer.
   - input == char* , catches char from getchar(). */
#define getChar(input)                                                         \
{                                                                              \
    char _c_h_ = '\0';                                                         \
    if(((input) = getchar()) != '\n'){                                         \
        clear_buff(_c_h_);}                                                    \
} /* end getChar */

/* Get a single character from stdin and loop untill input is correct. 
   NOTE: sets the single character to a capital letter.
   - input  == char*, string to check for Y/N.
   - string == char*, message to print to the user via printf();.
   - ...    == ending variable length arguments placed in printf(string,...);. */
#define yesNo(input, string, ...)                                              \
{                                                                              \
    do                                                                         \
    {                                                                          \
        printf((string), __VA_ARGS__);                                         \
        getChar((input));                                                      \
        (input) = toupper((input));                                            \
    }while(input != 'Y' && input != 'N');                                      \
} /* end getChar_check #}}} */

/* Get a line of input from a buffer.
   Clears the buffer if required. 
   Input must be dealloced or on the heap for compilation.
   NOTE: Len becomes the length of the string WITHOUT the '\0' value.
   - input == char* , Pointer to fill with resulting string.
   - max   == int   , Max number of bytes to take in from file. 
   - filePntr == FILE*, the file pointer associated with the proper FD. 
   - inlen == the length of the string WITHOUT the '\0' value. */
#define getLineInput(input, max, filePntr, inlen)                              \
{                                                                              \
    char __c_h__ = '\0';                                                       \
    if((input) == NULL){                                                       \
        (input) = (char*) malloc(sizeof(char)*max);}                           \
    if((input) == NULL){                                                       \
        errExit("getLineInput: Failed to allocate input");}                    \
                                                                               \
    memset((input), '\0', max);                                                \
    fgets((input),(max),(filePntr));                                           \
    (inLen) = strlen((input)) - 1;                                             \
    if(input[(inLen)] == '\n'){                                                \
        input[(inLen)] = '\0';}                                                \
    else{                                                                      \
        clear_buff(__c_h__); }                                                 \
} /* end getLineInput */

/* Get a line of input from a buffer.
   Does NOT clear the input buffer.
   Input must be dealloced or on the heap for compilation.
   NOTE: Len becomes the length of the string WITHOUT the '\0' value.
   - input == char* , Pointer to fill with resulting string.
   - max   == int   , Max number of bytes to take in from file. 
   - filePntr == FILE*, the file pointer associated with the proper FD. 
   - inlen == the length of the string WITHOUT the '\0' value. */
#define getLineInput_noClear(input, max, filePntr, inlen)                      \
{                                                                              \
    char __c_h__ = '\0';                                                       \
    if((input) == NULL){                                                       \
        (input) = (char*) malloc(sizeof(char)*max);}                           \
    if((input) == NULL){                                                       \
        errExit("getLineInput: Failed to allocate input");}                    \
                                                                               \
    memset((input), '\0', max);                                                \
    fgets((input),(max),(filePntr));                                           \
    (inLen) = strlen((input)) - 1;                                             \
    if(input[(inLen)] == '\n'){                                                \
        input[(inLen)] = '\0';}                                                \
} /* end getLineInput_noClear */

/* Copy a variable ammount of characters from a buffer based on a given position.
   Place resulting string in resStr based on a given conditional. 
   resStr will be '\0' terminated.
   fd     == int  , File descriptor corresponding to inBuf.
   inBuf  == char*, buffer to copy from. Must not be NULL.
   resStr == char*, buffer to copy to.
   conditional == The conditionals desired in the copy process.
                  Example: inBuf[i] != ' ' && inBuf[i] != '\n' */
#define getBufString(fd, inBuf, bfPl, resStr, conditional)                     \
{                                                                              \
    int _TM_ = 0;                                                              \
    assert(bfPl != NULL && inBuf != NULL);                                     \
    for(_TM_ = 0; conditional; ++_TM_)                                         \
    {                                                                          \
        resStr[_TM_] = *bfPl;                                                  \
        ++bfPl;                  /* increase buff placement */                 \
        if(*bfPl == '\0'){       /* reached end of current buffer */           \
            setInpuBuf(fd, inBuf, bfPl);}                                      \
    } /* end for */                                                            \
    ++bfPl;                                                                    \
    resStr[_TM_] = '\0';                                                       \
    if(*bfPl == '\0'){ /* reached end of current buffer */                     \
        setInputBuf(fd, inBuf, bfPl);}                                         \
} /* end getBufString */

                    /* other */

/* Create a bit mask for a given range of bits. start, end. (lsb,msb).
   - start == int, Which bit from bit 0 to start the mask.
   - end   == int, Which bit greater than start to end the mask.
   - resMask == int, Where the resulting bit mask will be placed */
#define create_mask(start, end, resMask)                                       \
{                                                                              \
    int __INC_ = 0;                                                            \
    if((start) > (end)){                                                       \
        errmsg("create_mask: start > end, no mask was generated.");}           \
                                                                               \
    resMask = 0; /* just to make sure im not an idiot when i call this */      \
    for(__INC_ = (start); __INC_ <= (end); ++__INC_){                          \
        (resMask) |= 1 << __INC_;}                                             \
} /* end create_mask */

/* Adds all the ascii values in a character array together.
   - array == char*, String to be added together.                              
   - size  == size_t, size of the string.                                      
   - res   == int, resulting sum of the string. */
#define sumChars(array, size, res)                                             \
{                                                                              \
    int I_NC = 0;                                                              \
    for(I_NC = 0; I_NC < (size), ++I_NC){                                      \
        (res) += (array[I_NC]);}                                               \
} /* end sumChars */

/* TODO: Adjust this macro or make an alternate that can call a function with
         variable arguments, rather than just one argument. (i.e. free(pntr);) */
/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS could be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define apply_funct(type, funct, ...)                                          \
{                                                                              \
    void *stopper = (int[]){0};                                                \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};                       \
    int __i_;                                                                  \
                                                                               \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){                        \
        (funct)(apply_list[__i_]);}                                            \
} /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define free_all(...)   apply_funct(void, free, __VA_ARGS__)
#endif
