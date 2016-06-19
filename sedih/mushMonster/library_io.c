 NOT STARTED NOT STARTED NOT STARTED */


#define __SED_ERR__
#define __SED_NUM__
#define __SED_LINUX__
#include "../sedhead/sedhead.h"

#define IN_BUF_ 50

/* takes in the input, an array to fill with resulting samples.
   inbuff = input
   resSamples = results of samples into integers
   numSamples = number of samples
   delimString = delimiter string used in strTok */
/* TODO: I need to realloc the buffer if failure. The things required for this
         are inside getLineInput, we need the bytes read, and need to read
         from that point.
         Maybe fread is actually the way to go if i dont know the length of 
         something but i know i need all of it. */
#define get_samples(file, inBuff, resSamples, numSamples, delimString)         \
{                                                                              \
    int _J = 0;                                                                \
    char *_TMP_ = NULL;                                                        \
    getLineInput(inBuff, IN_BUF_, stdin, inLen);                               \
    /* initiate strtok with buffer */                                          \
    _TMP_ = strtok(inBuff, delimString);                                       \
    resSamples[0] = getInt(_TMP_, 0, "_TMP_");                                 \
    for(_J = 1; _J < numSamples; ++_J)                                         \
    {                                                                          \
        _TMP_ = strtok((char*)NULL, delimString);                              \
        if(_TMP_ == NULL && inBuff[inLen] != '\0')                             \
        {                                                                      \
            getLineInput(inBuff, IN_BUF_, stdin, inLen);                       \
            _TMP_ = strtok(inBuff, delimString);                               \
            resSamples[_J] = getInt(_TMP_, 0, "_TMP_");                        \
        }                                                                      \
        else{                                                                  \
        resSamples[_J] = getInt(_TMP_, 0, "resSamples");}                      \
    }                                                                          \
} /* end get_samples */

/* method 1 of the mushroom monster problem */
static int method_one(int *Restrict samples, int sampNum)/*#{{{*/
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
static int method_two(int *Restrict samples, int sampNum)/*#{{{*/
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
        if(prev > cur && (prev - cur) > mps){
        mps = prev - cur;}

        prev = cur;
    }
    
    /* find solution to method 2 */
    for(i = 0; i < sampNum-1; ++i)
    {
        prev = samples[i];
        if(prev <= mps){
            min += prev;}
        else{
            min += mps;}

        prev = cur;
    }

    return min;
}/* end #}}} */

/* executes method one and returns the results in an int corresponding
   to the result that will be printed. returns the samples min.*/
static int gather_results(int *result[])/*#{{{*/
{
    int numTests = 0;   /* number of tests in file */
    int sampNum  = 0;   /* ammount of samples */
    int minOne, minTwo; /* method 1/2 current min */
    int i;              /* increments */
    int inLen;          /* length of string w/o '\0/' */
    int *samples = NULL;/* the given sampNum of samples */

    char *inBuff = NULL;/* input buffer */
    i = minOne = minTwo = inLen = 0;
    
    /* get number of tests */
    getLineInput(inBuff, IN_BUF_, stdin, inLen);
    numTests = getInt(inBuff, 0, "numTests");

    /* allocate room for method 1 and method two results */
    result[0] = (int*) malloc(sizeof(int)*numTests);
    result[1] = (int*) malloc(sizeof(int)*numTests);
    if(result[0] == NULL || result[1] == NULL){
        errExit("gather_results: allocation failure for result");}

    for(i = 0; i < numTests; ++i)
    {
        minOne = 0;
        minTwo = 0;

        /* get input from #of samples */
        getLineInput(inBuff, IN_BUF_, stdin, inLen);
        sampNum = getInt(inBuff, 0, "sampNum");

        samples = (int*) malloc(sizeof(int)*sampNum);
        if(result[0] == NULL || result[1] == NULL){
            errExit("gather_results: allocation failure for samples");}

        /* fill the array of samples */
        get_samples(inBuff, samples, sampNum, " ")

        /* get the two minimums */
        minOne = method_one(samples, sampNum);
        minTwo = method_two(samples, sampNum);

        /* fill result */
        result[0][i] = minOne;
        result[1][i] = minTwo;

        free(samples);
    }

    free(inBuff);

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

int main()
{
    int *result[2] = {NULL};
    int numTests = 0;

    numTests = gather_results(result);
    display_results(result, numTests);
    //free_all(result[0], result[1]);
    free(result[0]);
    free(result[1]);

    exit(EXIT_SUCCESS);
}

