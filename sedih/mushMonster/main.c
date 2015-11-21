/* header for the mush problem */
#define __SED_ERR__
#define __SED_NUM__
#define __SED_LINUX__
#include "../sedhead/sedhead.h"

#define IN_BUF_ 512
#define TM_BUF_ 16

/* allocate an input buffer with a '\0' terminatior at the end */
#define alloc_buff(fd, buff)                                                   \
{                                                                              \
    ssize_t _retBytes = 0;                                                     \
    if((_retBytes = read(fd, (void*) buff, IN_BUF_-1)) == -1){                 \
        errExit("alloc_buf(): read() failure");}                               \
    (_retBytes < IN_BUF_-1) ? (buff[_retBytes] = '\0')                         \
                            : (buff[IN_BUF_-1] = '\0');                        \
} 

/* reset the input buffer after first allocation */
#define setBuf(fd, buff, bfPl)                                                 \
{                                                                              \
    alloc_buff(fd, buff);                                                      \
    bfPl = buff;                                                               \
}

/* get the number string from the input buffer */
#define getNumString(fd, inBuf, bfPl, resStr, conditional)                     \
{                                                                              \
    int _TM_ = 0;                                                              \
    for(_TM_ = 0; conditional; ++_TM_)                                         \
    {                                                                          \
        resStr[_TM_] = *bfPl;                                                  \
        ++bfPl;                  /* increase buff placement */                 \
        if(*bfPl == '\0'){ /* reached end of current buffer */                 \
            setBuf(fd, inBuf, bfPl);}                                          \
    } /* end for */                                                            \
    ++bfPl;                                                                    \
    resStr[_TM_] = '\0';                                                       \
    if(*bfPl == '\0'){ /* reached end of current buffer */                     \
        setBuf(fd, inBuf, bfPl);}                                              \
} /* end getNumString */

/* method 1 of the mushroom monster problem */
static int method_one(int *samples, int sampNum)/*#{{{*/
{
    int res  = 0;
    int prev = 0;
    int cur  = 0;
    int i    = 0;

    prev = samples[0];
    for(i = 1; i < sampNum; ++i)
    {
        cur = samples[i];
        if(prev > cur){
            res += (prev - cur);}
        prev = cur;
    }
    return res;
} /* end method_one #}}} */

/* method 2 of the mushroom monster problem */
static int method_two(int *samples, int sampNum)/*#{{{*/
{
    int min  = 0;
    int mps  = 0; /* mushrooms per second */
    int prev = 0;
    int cur  = 0;
    int i    = 0;

    /* find the mushrooms per second eaten */
    prev = samples[0];
    for(i = 1; i < sampNum; ++i)
    {
        cur = samples[i];
        if(prev > cur){
        mps = ((prev - cur) > mps) ? (prev - cur) : mps;}

        prev = cur;
    }
    
    /* find solution to method 2 */
    prev = samples[0];
    for(i = 1; i < sampNum; ++i)
    {
        cur = samples[i];
        if(prev < cur){
            min += prev;}
        else{
            min += (cur == 0 && prev < mps) ? prev : mps;}

        prev = cur;
    }

    return min;
}/* end #}}} */


/* executes method one and returns the results in an int corresponding
   to the result that will be printed. returns the samples min.*/
static int gather_results(int fd, int *result[])/*#{{{*/
{
    int numTests = 0;   /* number of tests in file */
    int sampNum  = 0;   /* ammount of samples */
    int minOne, minTwo; /* method 1/2 current min */
    int i, j;           /* increments */
    int *samples = NULL;/* the given sampNum of samples */

    char *bufPl = NULL;            /* current place in input buffer */
    char inBuff[IN_BUF_] = {'\0'}; /* input buffer */
    char numStr[TM_BUF_] = {'\0'}; /* string to be converted */
    i = j = minOne = minTwo = 0;
    
    /* fill the input buffer */
    setBuf(fd, inBuff, bufPl);
    
    /* get number of tests */
    getNumString(fd, inBuff, bufPl, numStr, *bufPl != '\n');
    numTests = getInt(numStr, 0, "numTests");

    /* allocate room for method 1 and method two results */
    result[0] = (int*) malloc(sizeof(int)*numTests);
    result[1] = (int*) malloc(sizeof(int)*numTests);

    for(i = 0; i < numTests; ++i)
    {
        minOne = 0;
        minTwo = 0;

        /* get input from #of samples */
        getNumString(fd, inBuff, bufPl, numStr, *bufPl != '\n');
        sampNum = getInt(numStr, 0, "sampNum");

        samples = (int*) malloc(sizeof(int)*sampNum);

        /* fill the array of samples */
        for(j = 0; j < sampNum; ++j)
        {
            getNumString(fd, inBuff, bufPl, numStr, *bufPl != '\n' && *bufPl != ' ');
            samples[j] = getInt(numStr, 0, "cur");
        }

        /* get the two minimums */
        minOne = method_one(samples, sampNum);
        minTwo = method_two(samples, sampNum);

        /* fill result */
        result[0][i] = minOne;
        result[1][i] = minTwo;

        free(samples);
    }

    return numTests;
} /* end gather_results #}}} */

/* print the results of each method */
static inline void display_results(int *result[], int numTests)/*#{{{*/
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

int main(int argc, char *argv[])
{
    int *result[2] = {NULL};
    int numTests = 0;
    int fd       = 0;   /* file descriptor */

    if(argc != 2){
        noerrExit("CommandLine argument: invalid number of arguments\n$cmd path");}

    /* open the sample file */
    fd = open(argv[1], O_RDWR);
    if(fd == -1){
        errExit("gather_results: Opening file failed");}

    numTests = gather_results(fd, result);
    display_results(result, numTests);
    free_all(result[0], result[1]);

    /* close the sample file */
    if(close(fd) == -1){
        errExit("gather_results: close() failure");}

    exit(EXIT_SUCCESS);
}

