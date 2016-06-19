#define __SED_ERR__
#define __SED_NUM__
#define __SED_LINUX__
#include "../sed/sedhead.h" /* my header */


/*  
    - res        , long, result of check. Holds barbNum index if true.
    - openBarbs  , int*, list of open barber index numbers.
    - placeInLine, int, current place in line.
    - numAvail   , number of available barbers.
            >-1, returns the barber number. (the index in barbers array) of
                 person of interests barber */
#define CHECK_IF_NEXT(res, openBarbs, placeInLine, numAvail)                   \
{                                                                              \
    res = ((placeInLine > numAvail) ? -1 : (openBarbs[placeInLine-1] + 1));    \
    if(res == -1) {placeInLine -= numAvail;} /* set new place in line */       \
} /* end CHECK_IF_NEXT */

/* fills variables with proper data from file.
   Exits on error.
   returns array of barbers */
unsigned long* get_data(FILE *Restrict data, unsigned long *placeInLine, unsigned long *totalBarbs)
{
#define LNBUF    1024
#define RBUF     16
    char buff[LNBUF]  = {'\0'};
    char *bufPl = buff;
    char resStr[RBUF] = {'\0'};
    unsigned long *barber = NULL;
    unsigned int i = 0;

    /* get first line's information */
    FGETS_NOCLR_NLINE(buff, LNBUF, data);
    bufPl = buff;
   
    /* get number of barbers */
    FGETS_NEXT_LINE(data, buff, LNBUF, bufPl, resStr, ' ');
    *totalBarbs = getu64_t(resStr, 0, "get_data: totalBarbs");

    /* get place in line */
    FGETS_NEXT_LINE(data, buff, LNBUF, bufPl, resStr, ' ');
    *placeInLine = getu64_t(resStr, 0, "get_data: totalBarbs");

    /* fill barber with times */
    barber = (unsigned long*) malloc(sizeof(unsigned long) * (*totalBarbs));
    if(barber == NULL) {errExit("GET_DATA: barber, malloc failure");}

    FGETS_NOCLR_NLINE(buff, LNBUF, data);
    bufPl = buff; /* readjust place in buffer to the start */
    for(i=0; i < *totalBarbs; ++i)
    {
        FGETS_NEXT_LINE(data, buff, LNBUF, bufPl, resStr, ' ');
        barber[i] = getu64_t(resStr,0,"barber");
    } /* end for */

    return barber;
#undef LNBUF
#undef RBUF
} /* end GET_DATA */

/* gathers an array holding barber numbers (index numbers) of open barbers. 
   Returns array of integers that point to open barber index's */
unsigned long* gatherOpenBarbs(unsigned long *Restrict barber, unsigned long *Restrict numAvail, unsigned long presentTime, unsigned long numOfBarbs)
{
    unsigned long *temp = NULL;
    unsigned long *openBarbs = NULL; /* array of barber index's who are available */
    unsigned long b = 0;          /* barber increment */
    unsigned long t = 0; /* temp increment */
    
    if(presentTime > 0)
    {

        temp = (unsigned long*) malloc(sizeof(unsigned long)*numOfBarbs);
        if(temp == NULL) {errExit("gatherOpenBarbs: temp malloc fail.");}
        for(b=0; b < numOfBarbs; ++b)
        {
            /* check if barber is available */
            if((presentTime % barber[b]) == 0)
            {
                temp[t] = b;
                ++t;
            } /* end if */
        } /* end for */
        
        *numAvail = t;
        openBarbs = (unsigned long*) malloc(sizeof(unsigned long)*t);
        if(openBarbs == NULL) {errExit("gatherOpenBarbs: openBarbs malloc fail.");}

        for(b=0; b < t; ++b){
            openBarbs[b] = temp[b];}

        free(temp);
    }
    else
    {
        *numAvail = numOfBarbs;
        openBarbs = (unsigned long*) malloc(sizeof(unsigned long)*numOfBarbs);
        if(openBarbs == NULL) {errExit("gatherOpenBarbs: openBarbs malloc fail.");}

        for(b=0; b < numOfBarbs; ++b){
            openBarbs[b] = b;}
    }

    return openBarbs;
} /* end gatherOpenBarbs */

/* return barber noted person in line will have. */
unsigned long findBarbResult(FILE *Restrict testData)
{
    unsigned long  *barber    = NULL; /* array of barbers, each holding their cut time. */
    unsigned long *openBarbs = NULL;  /* array of barber index's who are available */

    unsigned long time        = 0;  /* unsigned long ass waits. */
    long barbResult  = 0;  /* resulting barb num */
    unsigned long placeInLine = 0;  /* current place in line */
    unsigned long numAvail   = 0;   /* holds the current number of available barbers. */

    unsigned long totalBarbs = 0;    /* total number of barbers for test case */


    barber = get_data(testData, &placeInLine, &totalBarbs);

    do{
        openBarbs = gatherOpenBarbs(barber, &numAvail, time, totalBarbs);
        CHECK_IF_NEXT(barbResult, openBarbs, placeInLine, numAvail);
        ++time;
      }while(barbResult == -1);
    
    FREE_ALL(barber, openBarbs);
    return barbResult;
} /* end findBarbResult */


/* argv[0] == program name, argv[1] == testfile. argc == 2 */
int main(int argc, char *argv[])
{
#define BUF_MAX 10
    FILE *testData = NULL; 

    size_t len     = 0;           /* length of input, not including '\0' */
    unsigned long i = 1;
    int numOfTests = 0;           /* number of tests in the file */
    long testResult = 0;           /* barber available from place in line */

    char buff[BUF_MAX] = {'\0'};  /* buffer to gather number of tests */

    if(argc != 2) {noerrExit("Invalid command: $ cmd testfilePath");}

    testData = fopen(argv[1],"r+");
    if(testData == NULL) {errExit("main: failure to open test file passed");}

    /* read in number of test cases, convert to int */
    FGETS_NOCLR(buff, BUF_MAX, testData, len);
    numOfTests = getInt(buff, 0, "main: numOfTests");

    /* execute each case */
    do
    {
        testResult = findBarbResult(testData);  
        printf("\nCase #%lu: %ld", i, testResult);
        --numOfTests;
        ++i;
    }while(numOfTests > 0);

    fclose(testData);

    exit(EXIT_SUCCESS);
}
