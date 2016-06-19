/*
    file: get_num.h
    
    Turns a string of characters into a their numerical equivilance using
    strtoul, and error checking the results.

    referenced from linux programming interface handbook.
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "get_num.h"


                    /* static functions */

                /* static prototypes #{{{ */ 
/* aborts program if anything fails. change exit to a return if needed */
static void 
gnFail(const char *fname, const char *msg, const char *arg, const char *name);

/* converts arg to a long, based on flags. fname and name used in error */
static long long
getNum(const char *fname, const char *arg, int32_t flags, const char *name);

/* converts arg to a long, based on flags. fname and name used in error */ 
static unsigned long long 
getUnsigned(const char *fname, const char *arg, register int32_t flags, const char *name);
/*#}}}*/

void gnFail(const char *fname, const char *msg, const char *arg, const char *name)/*#{{{*/
{
    fprintf(stderr, "%s error", fname);

    /* print original callers name if it was given */
    if(name != NULL){         
        fprintf(stderr, " (intType %s)", name);}

    fprintf(stderr, ": %s\n", msg);

    /* print the argument that was invalid */
    if(arg != NULL && arg != '\0'){   
        fprintf(stderr, "\t     offending text: %s\n", arg);}

    exit(EXIT_FAILURE);
} /* end fnFail #}}}  */

long long getNum(const char *fname, const char *arg, register int32_t flags, /*#{{{*/
                 const char *name)
{
    register long long res = 0;
    register int32_t base = 0;
    char *endptr = NULL;

    if(arg == NULL || *arg == '\0'){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nNull or empty string.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "null or empty string", arg, name);} 
    } 

    /* determine the base to be passed to strtoul. */
    base = (flags & GN_BASE_10) ? 10 :
           (flags & GN_BASE_16) ? 16 :
           (flags & GN_BASE_8)  ? 8  : 0;

    errno = 0; /* just in case errno was set from who knows where */
    res = strtoll(arg, &endptr, base); /* convert string to base */
    
    /* error check result */
    if(errno != 0){   
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nConversion failed.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "strtoll() failed", arg, name);} /* end else */
    }

    if(*endptr != '\0'){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nNonnumeric characters.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "nonnumeric characters", arg, name);}
    } 

    if((flags & GN_NONEG) && res < 0){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nNegetive value not allowed.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "negative value not allowed", arg, name);}
    }

    if((flags & GN_GT_O) && res <= 0){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nValue must be > 0.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "value must be > 0", arg, name);}
    } 
    return res; 
} /* end getNum #}}} */

unsigned long long getUnsigned(const char *fname, const char *arg,     /*#{{{*/
                               register int32_t flags, const char *name)
{
    register unsigned long long res = 0;
    register int32_t base = 0;
    char *endptr = NULL;

    if(arg == NULL || *arg == '\0'){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nNull or empty string.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "null or empty string", arg, name);} 
    } 

    /* determine the base to be passed to strtoul. */
    base = (flags & GN_BASE_10) ? 10 :
           (flags & GN_BASE_16) ? 16 :
           (flags & GN_BASE_8)  ? 8  : 0;

    errno = 0; /* just in case errno was set from who knows where */
    res = strtoull(arg, &endptr, base); /* convert string to base */
    
    /* error check result */
    if(errno != 0){   
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nConversion failed.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "strtoll() failed", arg, name);}
    }

    if(*endptr != '\0'){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nNonnumeric characters.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "nonnumeric characters", arg, name);}
    } 

    if((flags & GN_GT_O) && res <= 0){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nValue must be > 0.\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail(fname, "value must be > 0", arg, name);}
    } 
    return res; 
} /* end getUnsigned #}}} */

                    /* header functions */

long getLong(const char *arg, int32_t flags, const char *varName)/*#{{{*/
{
    register long long res = 0;
    
    res = getNum("getLong", arg, flags, varName);

    /* make sure the converted number is in the range of an long */
    if(res > LONG_MAX || res < LONG_MIN){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nInteger was out of range\n");
            errno = EINVAL;
            return 0;}
        else{
            gnFail("getInt", "integer out of range", arg, varName);}
    }
    return (long) res; 
} /* end getLong #}}} */

int getInt(const char *arg, int32_t flags, const char *varName)/*#{{{*/
{
    register long long res = 0;

    res = getNum("getInt", arg, flags, varName);
    
    /* make sure the converted number is in the range of an int */
    if(res > INT_MAX || res < INT_MIN){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nInteger was out of range\n");
            return 0;}
        else{
        gnFail("getInt", "integer out of range", arg, varName);}
    }
    return (int) res;
} /* end getInt #}}}*/

int32_t get32_t(const char *arg, int32_t flags, const char *varName)/*#{{{*/
{
    register long long res = 0;

    res = getNum("get32_t", arg, flags, varName);
    
    /* make sure the converted number is in the range of an int32_t */
    if(res > INT32_MAX || res < INT32_MIN){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nInteger was out of range\n");
            errno = EINVAL;
            return 0;}
        else{
        gnFail("getInt", "integer out of range", arg, varName);}
    } /* end if */
    return (int32_t) res;
} /* end get32_t #}}} */

int64_t get64_t(const char *arg, int32_t flags, const char *varName)/*#{{{*/
{
    register long long res = 0;

    res = getNum("get64_t", arg, flags, varName);

    /* make sure the converted number is in the range of an int64_t */
    if(res > INT64_MAX || res < INT64_MIN){
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nInteger was out of range\n");
            errno = EINVAL;
            return 0;}
        else{
        gnFail("getInt", "integer out of range", arg, varName);}
   } 
    return (int64_t) res;
} /* end get64_t #}}} */

uint32_t getu32_t(const char *arg, int32_t flags, const char *varName)/*#{{{*/
{
    register unsigned long long res = 0;

    res = getUnsigned("getu32_t", arg, flags, varName);
    
    /* make sure the converted number is in the range of an uint32_t */
    if(res > UINT32_MAX){ /* checks for >0 in getNum */
        if(flags & GN_NOEXIT_){
            errno = EINVAL;
            fprintf(stderr,"\nInteger was out of range\n");
            return 0;}
        else{
        gnFail("getInt", "integer out of range", arg, varName);}
    }
    return (uint32_t) res;
} /* end get32_t #}}} */

uint64_t getu64_t(const char *arg, int32_t flags, const char *varName)/*#{{{*/
{
    register unsigned long long res = 0;

    res = getUnsigned("getu64_t", arg, flags, varName);

    /* make sure the converted number is in the range of an uint64_t */
    if(res > UINT64_MAX){ /* checks for unsigned in getNum */
        if(flags & GN_NOEXIT_){
            fprintf(stderr,"\nInteger was out of range\n");
            errno = EINVAL;
            return 0;}
        else{
        gnFail("getUnsigned", "integer out of range", arg, varName);}
    } 
    return (uint64_t) res;
} /* end get64_t #}}} */

