#include "mush.h"
#include <limits.h>

#define IN_BUF_ INT_MAX
#define TM_BUF_ 11 /* an integer is only up to 10 digits, I.E 10 characters. */


/* fill the input buffer */
#define alloc_buff(buffer)                                          \
{                                                                   \
    int _retBytes = 0;                                              \
    _retBytes = read(fd, (void*)buffer, IN_BUF_);                    \
    if(_retBytes != IN_BUF_){ /* Potential newline at end of file */ \
        buffer[_retBytes-1] = '\0';}                                 \
}

/* buffer to get information from (char*). Where to place the result (char*),
   Current index inside of buffer. ... are the stopping conditionals */
#define getBufLine(buffer, res, bfPl)                                            \
{                                                                                \
    int _TM_ = 0;                                                                \
    for(_TM_ = 0;  buffer[bfPl] != '\n' && buffer[bfPl] != ' '; ++_TM_, ++(bfPl))\
    {                                                                            \
        res[_TM_] = buffer[(bfPl)];                                              \
        if(bfPl == IN_BUF_)                                                      \
        {                                                                        \
            printf("\ninside %d\n", bfPl);\
            alloc_buff(buffer);                                                  \
            bfPl = 0;                                                            \
        }                                                                        \
    }                                                                            \
    ++bfPl; /* skip delimiter */                                                 \
    res[_TM_] = '\0';                                                            \
}

int main()
{
    int *result[2] = {NULL};
    gather_results(result);
    free_all(result[0], result[1]);
    exit(EXIT_SUCCESS);
}

int gather_results(int *result[])
{
    int fd       = 0;       /* file descriptior */
    int minOne   = 0;       /* minimum method 1 */
    int numTests = 0;       /* number of tests in file */
    int sampNum  = 0;       /* ammount of samples */
    int prevVal  = 0;       /* previous sample values */
    int curVal   = 0;       /* current sample value */
    int bfPl     = 0;       /* place from inBuff */
    int i        = 0;
    int j        = 0;
    ssize_t retBytes = 0;   /* byte value returned from a read or write */
    char inBuff[IN_BUF_] = {'\0'};  /* input buffer */
    char numStr[TM_BUF_] = {'\0'};  /* String to be converted to an int from buf */
    
    fd = open("smallpractice", O_RDWR);
    if(fd == -1){
        errExit("gather_results: Opening file failed");}
    
    /* fill the input buffer */
    alloc_buff(inBuff);
   
    /* get number of tests */
    getBufLine(inBuff, numStr, bfPl);
    numTests = getInt(numStr, 0, "numTests");

    result[0] = (int*) malloc(sizeof(int)*numTests);
    result[1] = (int*) malloc(sizeof(int)*numTests);

    /* allocate results index 0 and 1. */
    for(i = 0; i < numTests; ++i)
    {
        minOne = 0;
        /*minTwo = 0;*/
        
        /* get input from #of samples */
        getBufLine(inBuff, numStr, bfPl);
        sampNum = getInt(numStr, 0, "sampNum");

        /* pull first sample from file */
        getBufLine(inBuff, numStr, bfPl);
        prevVal = getInt(numStr, 0, "prevVal");

        --sampNum; /* prevVal holds the first sample */
        for(j = 0; j < sampNum; ++j)
        {
            getBufLine(inBuff, numStr, bfPl);
            curVal = getInt(numStr, 0, "curVal");
            
            /* get the mins */
            minOne += method_one(prevVal, curVal);
            /* minTwo += method_two() */

            prevVal = curVal;
        }

        if(sampNum == 0)
        {
            minOne = prevVal;
            /*results[1][i] = prevVal;*/
        }

        /* place result in correct place */
        result[0][i] = minOne;
        /* result[1][i] = minTwo; */
    } 
    
    if(close(fd) == -1){
        errExit("gather_results: close() failure");}

    return 1;
}



int method_one(int prev, int cur)
{
    int res = 0;

    if(prev > cur)
    {
        res = (prev - cur);
        return res;
    }
    return 0;
}


void display_results(int *result[], int numTests)
{


}
