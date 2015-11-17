#include "mush.h"

#define IN_BUF_ 512
#define TM_BUF_ 16

/* allocate an input buffer */
#define alloc_buff(buff)                                                       \
{                                                                              \
    ssize_t _retBytes = 0;                                                     \
    if((_retBytes = read(fd, (void*) buff, IN_BUF_-1)) == -1){                         \
        errExit("alloc_buf(): read() failure");}                               \
    (_retBytes < IN_BUF_-1) ? (buff[_retBytes] = '\0')                         \
                            : (buff[IN_BUF_-1] = '\0');                        \
} /* end alloc_buff */

/* reset the input buffer after first allocation */
#define setBuf(buff, bfPl)                                                     \
{                                                                              \
    alloc_buff(buff);                                                          \
    bfPl = buff;                                                               \
} /* end resetBuf */

/* get the number string from the input buffer */
#define getNumString(inBuf, bfPl, resStr)                                      \
{                                                                              \
    int _TM_ = 0;                                                              \
    for(_TM_ = 0; *bfPl != '\n' && *bfPl != ' '; ++_TM_)                       \
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
} /* end alloc_bff */

int main()
{
    int *result[2] = {NULL};
    int numTests = 0;
    numTests = gather_results(result);
    display_results(result, numTests);
    free_all(result[0], result[1]);
    exit(EXIT_SUCCESS);
}

int gather_results(int *result[])/*#{{{*/
{
    int fd       = 0;   /* file descriptor */
    int numTests = 0;   /* number of tests in file */
    int sampNum  = 0;   /* ammount of samples */
    int minOne, minTwo; /* method 1/2 current min */
    int prev, cur;      /* prev/cur sample value */
    int i, j;           /* increments */

    char *bufPl = NULL;            /* current place in input buffer */
    char inBuff[IN_BUF_] = {'\0'}; /* input buffer */
    char numStr[TM_BUF_] = {'\0'}; /* string to be converted */
    i = j = minOne = minTwo = prev = cur = 0;
    
    /* open the sample file */
    fd = open("largePractice", O_RDWR);
    if(fd == -1){
        errExit("gather_results: Opening file failed");}
    
    /* fill the input buffer */
    setBuf(inBuff, bufPl);
    
    /* get number of tests */
    getNumString(inBuff, bufPl, numStr);
    numTests = getInt(numStr, 0, "numTests");

    /* allocate room for method 1 and method two results */
    result[0] = (int*) malloc(sizeof(int)*numTests);
    result[1] = (int*) malloc(sizeof(int)*numTests);

    for(i = 0; i < numTests; ++i)
    {
        minOne = 0;
        minTwo = 0;

        /* get input from #of samples */
        getNumString(inBuff, bufPl, numStr);
        sampNum = getInt(numStr, 0, "sampNum");

        /* pull first sample from file */
        getNumString(inBuff, bufPl, numStr);
        prev = getInt(numStr, 0, "prev");

        --sampNum; /* prevVal holds the first sample */
        for(j = 0; j < sampNum; ++j)
        {
            /* get next value in the buffer */
            getNumString(inBuff, bufPl, numStr);
            cur = getInt(numStr, 0, "cur");
            
            /* gather the minimums */
            minOne += method_one(prev, cur);
            minTwo += method_two(sampNum+1, prev,  cur);

            prev = cur;
        }
        
        /* if there was only 1 sample --; */
        if(sampNum == 0)
        {
            minOne = prev;
            minTwo = prev;
        }
        
        /* fill result */
        result[0][i] = minOne;
        result[1][i] = minTwo;
    }

    if(close(fd) == -1){
        errExit("gather_results: close() failure");}

    return numTests;
} /* end gather_results #}}} */

int method_one(int prev, int cur)/*#{{{*/
{
    int res = 0;

    if(prev > cur)
    {
        res = (prev - cur);
        return res;
    }
    return 0;
} /* end method_one #}}} */

int method_two(int sampNum, int prev, int cur)/*#{{{*/
{
#define MEPI 10 /* min eaten per interval */
    int min = (sampNum * MEPI);

    if(prev < cur){
        min = prev;}
    else{
        min = 10;}
    return min;
#undef MEPI
} /* end method_two #}}} */

void display_results(int *result[], int numTests)/*#{{{*/
{
#define TM_BF_  4096
    int i = 0;
    char temp[TM_BF_] = {'\0'};
    
    if(result == NULL || *result == NULL){
        errExit("display_results(): *result[] was NULL");}
   
    for(i = 0; i < numTests; ++i)
    {
        snprintf(temp, TM_BF_,"\nCase %d: %d %d", 
                 i+1, result[0][i], result[1][i]);
        write(STDOUT_FILENO, temp, strlen(temp));
    }
#undef TM_BF_
} /* end display_results #}}} */
