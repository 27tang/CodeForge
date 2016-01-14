/*
    stuff i use for stuff.


    I really want to know how i should handle increments in for loops in 
    my macros.
        Have them pass an increment variable?
                         ||
        Have the mixed declaration and declare it with random __'s.

    I just need to research how mixed declarations are implemented by
    the compilers that do it, and how certian standards handle it.
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
#include <errno.h>

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
       If nothing is read, buff[0] = '\0'.
       - fd    == int   , File descriptor used for allocInputBuff()
       - buff  == char* , Buffer to be filled with character data from fd.
       - nbyte == size_t, number of bytes to read, including room for '\0'. 
                        (typically the size of buffer array) */
    #define readInput(fd, buff, nByte)                                         \
    {                                                                          \
        ssize_t _retBytes = 0;                                                 \
        --nByte; /* leave room for '\0' */                                     \
        if((_retBytes = read(fd, (void*) buff, nByte)) == -1){                 \
            errExit("alloc_buf(): read() failure");}                           \
        (_retBytes < nByte) ? (buff[_retBytes] = '\0')                         \
                                : (buff[nByte] = '\0');                        \
        ++nByte; /* set nByte back to original value */                        \
    } /* end readInput */

    /* Copy a variable ammount of characters from a buffer based on a given 
       position.
       Place resulting string in resStr based on a given conditional. 
       resStr will be '\0' terminated.
       NOTE: Typically used in specific steps or in a while loop. 
       - fd     == int  , File descriptor corresponding to inBuf.
       - inBuf  == char*, buffer to copy from. Must not be NULL.
       - bfPl   == char*, the current location inside inBuf. (init: bfPl = inBuf)
       - resStr == char*, buffer to copy to.
       - nbyte  == size_t, number of bytes to read, including room for '\0'. 
                        (typically the size of buffer array)
       - conditional == The conditionals desired in the copy process.
                      Example: inBuf[i] != ' ' && inBuf[i] != '\n' */
    #define read_nextFullFile(fd, inBuf, bfPl, nByte, resStr, conditional)     \
    {                                                                          \
        int _TM_ = 0;                                                          \
        assert(resStr != NULL && bfPl != NULL && inBuf != NULL);               \
        for(_TM_ = 0; conditional; ++_TM_)                                     \
        {                                                                      \
            resStr[_TM_] = *bfPl;                                              \
            ++bfPl;                  /* increase buff placement */             \
            if(*bfPl == '\0')                                                  \
            {   /* reached end of current buffer */                            \
                readInput(fd, inBuf, nByte);                                   \
                bfPl = inBuf;                                                  \
            }                                                                  \
        } /* end for */                                                        \
        ++bfPl;                                                                \
        resStr[_TM_] = '\0';                                                   \
        if(*bfPl == '\0')                                                      \
        {   /* reached end of current buffer */                                \
            readInput(fd, inBuf, nByte);                                       \
            bfPl = inBuf;                                                      \
        }                                                                      \
    } /* end readBuff_strRet */
#endif


#ifndef _LIL_FL_CONSTS__
#define _LIL_FL_CONSTS__
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
#ifndef __SED_BOOL_
#define __SED_BOOL_
    #ifdef true 
    #undef true
    #endif
    #ifdef false 
    #undef false 
    #endif
    typedef enum {false, true} Bool;
#endif

                    /* min/max */
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

                    /* input */

/* clears the input buffer using variable char ch; and getchar ().*/
#define clear_stdin()                                                          \
{                                                                              \
    char _CH_ = '\0';                                                          \
    while((_CH_ = getchar()) != '\n' && _CH_ != EOF);                          \
} /* end clear_stdin */

/* Get 1 character from stdin using getchar, clears input buffer.
   - input == char , catches char from getchar(). */
#define getChar(input)                                                         \
{                                                                              \
    if(((input) = getchar()) != '\n'){                                         \
        clear_stdin();}                                                        \
} /* end getChar */

/* Get a single character from stdin and loop untill input is correct. 
   NOTE: > sets the single character to a capital letter.
         > uses the above macro getChar(input), not getchar from the standard
           lib. 
           TODO: I will consider changing getChars name in the future
   - input  == char , string to check for Y/N.
   - string == char*, message to print to the user via printf();.
   - ...    == ending variable length arguments placed in printf(string,...);. */
#define yesNo(input, string, ...)                                              \
{                                                                              \
    /* TODO: Find out what happens with a statment like the following:         \
             assert("Some literal string" != NULL);                            \
             - It doesn have an address... but is it NULL? awkward statment. */\
    do                                                                         \
    {                                                                          \
        printf((string), __VA_ARGS__);                                         \
        getChar(input);                                                        \
        (input) = toupper((input));                                            \
    }while(input != 'Y' && input != 'N');                                      \
} /* end getChar_check #}}} */

/* Get a line of input from a buffer.
   Clears the buffer if required. 
   Input must be dealloced or on the heap for compilation.
   NOTE: Len becomes the length of the string WITHOUT the '\0' value.
   - input    == char* , Pointer to fill with resulting string.
   - max      == int   , Max number of bytes to take in from file. 
   - filePntr == FILE* , the file pointer associated with the proper FD. 
   - inlen    == size_t, the length of the string WITHOUT the '\0' value. */
#define fgetsInput(input, max, filePntr, inLen)                                \
{                                                                              \
    assert(input != NULL && filePntr != NULL);                                 \
    memset((input), '\0', max);                                                \
    fgets((input),(max),(filePntr));                                           \
    (inLen) = strlen((input)) - 1;                                             \
    if(input[(inLen)] == '\n'){                                                \
        input[(inLen)] = '\0';}                                                \
    else{                                                                      \
        clear_stdin(); }                                                       \
} /* end lineInput */

/* Get a line of input from a buffer.
   Does NOT clear the input buffer.
   Input must be dealloced or on the heap for compilation.
   NOTE: Len becomes the length of the string WITHOUT the '\0' value.
   - input    == char* , Pointer to fill with resulting string.
   - max      == int   , Max number of bytes to take in from file. 
   - filePntr == FILE* , the file pointer associated with the proper FD. 
   - inlen    == size_t, the length of the string WITHOUT the '\0' value. */
#define fgetsInput_noClear(input, max, filePntr, inLen)                        \
{                                                                              \
    assert(input != NULL && filePntr != NULL);                                 \
    memset((input), '\0', max);                                                \
    fgets((input),(max),(filePntr));                                           \
    (inLen) = strlen((input)) - 1;                                             \
    if(input[(inLen)] == '\n'){                                                \
        input[(inLen)] = '\0';}                                                \
} /* end lineInput_noClear */

/* Get a line of input from a buffer.
   Does NOT clear the input buffer.
   Does NOT remove newline.
   Input must be dealloced or on the heap for compilation.
   NOTE: Len becomes the length of the string WITHOUT the '\0' value.
   - input    == char* , Pointer to fill with resulting string.
   - max      == int   , Max number of bytes to take in from file. 
   - filePntr == FILE* , the file pointer associated with the proper FD. 
   - inlen    == size_t, the length of the string WITHOUT the '\0' value. */
#define fgetsInput_noClear_withNline(input, max, filePntr)                     \
{                                                                              \
    assert(input != NULL && filePntr != NULL);                                 \
    memset((input), '\0', max);                                                \
    fgets((input),(max),(filePntr));                                           \
} /* end lineInput_noClear_withNline */


/* Reads nmemb number of elements of dataSize into buff from fstream.
   fread is a binary read.
   Checks for eof and errors after fread is called.
   Does not place a null value, data is not garunteed as a char. 
   If a terminating null is required, leave room in buff and manually add it
   after the call to freadInput().
   Does not clear the input buffer.
   - buff == void*, buffer to place nmemb elements into
   - dataSize == size_t, size of the binary data being read from stream.
   - nmemb == size_t, number of items of dataSize to be read from fsteam.
   - fstream == FILE*, file pointer of input stream.*/
#define freadInput(buff, dataSize, nmemb, fstream)                             \
{                                                                              \
        assert(buff != NULL && fstream != NULL);                               \
        if(fread(buff, dataSize, nmemb, fstream) < nmemb)                      \
        {                                                                      \
            /* can ferror() tell you which error occured? Or is it just a      \
               general, yes some unknown error has occured? */                 \
            if(ferror(fstream) != 0){                                          \
                noerrExit("fread() failure.");}                                \
        }                                                                      \
}

/*  Copy a variable ammount of characters from a buffer based on a given 
    position.
    Place resulting string in resStr based on a given conditional. 
    resStr will be '\0' terminated.
    NOTE: inLen will be the length of the current buffer WITHOUT '\0'
          Typically used in specific steps or in a while loop. 
          End when a '\n' is found. The end of the full line.
    - filePntr    == FILE* , File pointer corresponding to inBuf.
    - inBuf       == char* , buffer to copy from. Must not be NULL.
    - max         == int   , Max number of bytes to take in from file.
                             (typically the size of the buffer array)
    - bfPl        == char* , the current location inside inBuf.
    - resStr      == char* , buffer to copy to.
    - conditional == The conditionals desired in the copy process.
                     Example: inBuf[i] != ' ' && inBuf[i] != '\n' */
#define fgets_nextFullLine(filePntr, inBuf, max, bfPl, resStr, conditional)\
{                                                                              \
    int _TM_ = 0;                                                              \
    assert(filePntr != NULL && resStr != NULL && bfPl != NULL && inBuf != NULL);\
    for(_TM_ = 0; conditional; ++_TM_)                                         \
    {                                                                          \
        resStr[_TM_] = *bfPl;                                                  \
        ++bfPl;                  /* increase buff placement */                 \
        if(*bfPl == '\0' && filePntr != stdin)                                 \
        {   /* set buffer */                                                   \
            fgetsInput_noClear_withNline(inBuf, max, filePntr);                \
            bfPl = inBuf;                                                      \
        }                                                                      \
    } /* end for */                                                            \
    ++bfPl;                                                                    \
    resStr[_TM_] = '\0';                                                       \
    if(*bfPl == '\0' && filePntr != stdin && *bfPl != '\n')                    \
    {   /* set buffer */                                                       \
        fgetsInput_noClear_withNline(inBuf, max, filePntr);                    \
        bfPl = inBuf;                                                          \
    }                                                                          \
}

/*  Copy a variable ammount of characters from a buffer based on a given 
    position.
    Place resulting string in resStr based on a given conditional. 
    resStr will be '\0' terminated.
    NOTE: inLen will be the length of the current buffer WITHOUT '\0'
          Typically used in specific steps or in a while loop. 
    - filePntr  == FILE*  , File pointer corresponding to inBuf.
    - inBuf     == char*  , buffer to copy from. Must not be NULL.
    - dataSize  == size_t , size of the data used in fread.
    - nmemb     == size_t , Max number of elements of dataSize to take from file.
                           (typically the size of the buffer array)
    - bfPl        == char*, the current location inside inBuf.
    - resStr      == char*, buffer to copy to.
    - conditional == The conditionals desired in the copy process.
                     Example: inBuf[i] != ' ' && inBuf[i] != '\n' */
#define fread_nextFullFile(filePntr, inBuf, dataSize, nmemb, bfPl, resStr, conditional)\
{                                                                              \
    int _TM_ = 0;                                                              \
    assert(filePntr != NULL && resStr != NULL && bfPl != NULL && inBuf != NULL);\
    for(_TM_ = 0; conditional; ++_TM_)                                         \
    {                                                                          \
        resStr[_TM_] = *bfPl;                                                  \
        ++bfPl;                  /* increase buff placement */                 \
        if(*bfPl == '\0' && filePntr != stdin)                                 \
        {   /* set buffer */                                                   \
            freadInput(inBuf, dataSize, nmemb, filePntr);                      \
            bfPl = inBuf;                                                      \
        }                                                                      \
    } /* end for */                                                            \
    ++bfPl;                                                                    \
    resStr[_TM_] = '\0';                                                       \
    if(*bfPl == '\0' && filePntr != stdin)                                     \
    {   /* set buffer */                                                       \
        freadInput(inBuf, dataSize, nmemb, filePntr);                          \
        bfPl = inBuf;                                                          \
    }                                                                          \
}

                    /* other */
/* resizes a given string into a properly sized array.
   if res is allready allocated, it is up to programmer to have it as correct
   size, otherwise proper size should be len+1.
   Does not deallocate string.
   - String, char*  == string to be resized.
   - len   , size_t == length of string not including terminating '\0'.
   - res   , char*  == resulting character pointer. */
#define resize_string(string, len, res)                                        \
{                                                                              \
    assert(string != NULL);                                                    \
    if(res == NULL){                                                           \
        res = (char*) malloc(sizeof(char)*len+1);}                             \
    strncpy(res, string, len+1);                                               \
}

/* Create a bit mask for a given range of bits. start, end. (lsb,msb).
   - start   == int, Which bit from bit 0 to start the mask.
   - end     == int, Which bit greater than start to end the mask.
   - resMask == int, Where the resulting bit mask will be placed */
#define create_mask(start, end, resMask)                                       \
{                                                                              \
    int __INC_ = 0;                                                            \
    if((start) < (end)){                                                       \
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
    if(array != NULL)                                                          \
    {                                                                          \
        for(I_NC = 0; I_NC < (size), ++I_NC){                                  \
            (res) += (array[I_NC]);}                                           \
    }                                                                          \
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
