#define __SED_ERR__
#define __SED_NUM__
#define __SED_LINUX__
#include "../sedhead/sedhead.h"

/* executes method one and returns the results in an int corresponding
   to the result that will be printed. returns the samples min */
int method_one(int prev, int cur);
/* goes through the file, pulls all the stuff, calls the methods for the stuff.
   that stuff.
   results[0] = method1;
   results[1] = method2; */
int gather_results(int *results[]);
/* print the results of each method */
void display_results(int *methOne, int numTests);

#define IN_BUF_ 1000000

int main()
{
    int *result[2] = {NULL};
    gather_results(result);
    free_all(result[0], result[1], result);
    exit(EXIT_SUCCESS);
}

int gather_results(int *result[])
{
    int minOne = 0;   /* minimum method 1 */
    int numTests = 0; /* number of tests in file */
    int sampNum  = 0; /* ammount of samples */
    int prevVal  = 0; /* previous sample values */
    int curVal   = 0; /* current sample value */
    int bfPl     = 0; /* place from inBuff */
    int tm       = 0; /* place in temp */
    int i        = 0;
    int j        = 0;
    int fd       = 0; /* file descriptior */
    ssize_t retBytes = 0; /* byte value returned from a read or write */
    char inBuff[IN_BUF_] = {'\0'};
    char temp[IN_BUF_ + 1] = {'\0'};
    
    /* open the file */
    fd = open("smallpractice", O_RDWR);
    if(fd == -1){
        errExit("gather_results: Opening file failed");}

    /* do the stuff with the file i/o ;) */
    retBytes = read(fd, (void*)inBuff, IN_BUF_);
    /* potential newline at end of file */
    if(retBytes != IN_BUF_){
        inBuff[retBytes-1] = '\0';}
    
    /* get input of first line. */
    for(tm = 0/*bfPl*/; inBuff[bfPl] != '\n'; ++tm, ++bfPl){
        temp[tm] = inBuff[bfPl];}
    ++bfPl; /* skip newline */
    temp[tm] = '\0';
    /* aquire the number represented */
    numTests = getInt(temp, 0, "numTests");

    /* allocate room for results */
    result[0] = (int*) malloc(sizeof(int)*numTests);
    result[1] = (int*) malloc(sizeof(int)*numTests);

    /* allocate results index 0 and 1. */
    for(i = 0; i < numTests; ++i)
    {
        minOne = 0;
        /* get input from #of samples */
        for(tm = 0 /*bfPl*/; inBuff[bfPl] != '\n'; ++tm, ++bfPl){
            temp[tm] = inBuff[bfPl];}
        ++bfPl;  /* skip newline */
        temp[tm] = '\0';
        /* aquire the number represented */
        sampNum = getInt(temp, 0, "sampNum");

        /* pull first sample from file */
        for(tm = 0; inBuff[bfPl] != ' ' && inBuff[bfPl] != '\n'; ++tm, ++bfPl){
            temp[tm] = inBuff[bfPl];}
        ++bfPl; /* skip newline or space */
        temp[tm] = '\0';
        prevVal = getInt(temp, 0, "prevVal");

        if(sampNum == 1){
            minOne = prevVal;
            /*results[1][i] = prevVal;*/}

        for(j = 0; j < sampNum-1 && sampNum != 1; ++j)
        {
            for(tm = 0; inBuff[bfPl] != ' ' && inBuff[bfPl] != '\n'; ++tm, ++bfPl){
                temp[tm] = inBuff[bfPl];}
            ++bfPl; /* skip newline or space */
            temp[tm] = '\0';
            curVal = getInt(temp, 0, "curVal");
            
            /* get the minimums */
            minOne += method_one(prevVal, curVal);
            /* minTwo += method_two() */

            /* set next previous */
            prevVal = curVal;
        } /* end for */

        /* place result in correct place */
        result[0][i] = minOne;
        /* result[1][i] = minTwo; */
    } 
    
    /* close the file */
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


void display_results(int *methOne, int numTests)
{


}
