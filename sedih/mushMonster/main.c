#include "mush.h"

#define IN_BUF_ 10000
#define TM_BUF_ 16

/* allocate an input buffer */
#define alloc_buff(buff)                                                       \
{                                                                              \
    ssize_t _retBytes = 0;                                                     \
    _retBytes = read(fd, (void*) buff, IN_BUF_-1);                             \
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
        if(*bfPl == '\0'){                                                     \
            setBuf(inBuf, bfPl);}                                              \
    } /* end for */                                                            \
    ++bfPl;                                                                    \
    resStr[_TM_] = '\0';                                                       \
} /* end alloc_bff */

int main()
{
    int *result[2] = {NULL};
    gather_results(result);
    free_all(result[0], result[1]);
    exit(EXIT_SUCCESS);
}

int gather_results(int *result[])
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
    fd = open("smallpractice", O_RDWR);
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
            getNumString(inBuff, bufPl, numStr);
            cur = getInt(numStr, 0, "cur");
            
            minOne += method_one(prev, cur);

            prev = cur;
        }
        
        /* if there was only 1 sample --; */
        if(sampNum == 0)
        {
            minOne = prev;
            minTwo = prev;
        }

        printf("\nminOne: %d\n", minOne);
        result[0][i] = minOne;
        result[1][i] = minTwo;

        //printf("\ncase: %d", minOne);
    }

    
    if(close(fd) == -1){
        errExit("gather_results: close() failure");}

    return 0;
} /* end gather_results */

int method_one(int prev, int cur)
{
    int res = 0;

    if(prev > cur)
    {
        res = (prev - cur);
        return res;
    }
    return 0;
} /* end method_one */
