#define __SED_ERR__
#define __SED_NUM__
#define __SED_LINUX__
#include "../sed/sedhead.h" /* my header */

/* fills variables with proper data from file
   - data, FILE* to testcase information. */
#define GET_DATA(data)

/* print the result! */
#define DISP_RESULT()

/* gathers an array holding barber numbers (index numbers) of open barbers. */
int* gatherOpenBarbs(int *barber, long presentTime, int numOfBarbs)
{
#define BARB_TMP
    int *temp[
    int *openBarbs = NULL; /* array of barber index's who are available */
    int i = 0;

    for(/*i=0*/; i < numOfBarbs; ++i)
    {
        /* check if barber is available */
        if((presentTime % barber[i]) == 0){

    }
}

/* fill all open chairs */
int fillOpenChairs();

/* Checks the next for barbResult.
   Return array is on the heap and must be free'd.

   Returns: -1 , if person of interest did not go into a barber seat.
            >-1, returns the barber number. (the index in barbers array) of
                 person of interests barber */
int checkForResult(int *openBarbs)
{


}

/* return barber noted person in line will have. */
int findBarbResult(FILE *testData)
{
    int *barber    = NULL; /* array of barbers, each holding their cut time. */
    int *openBarbs = NULL; /* array of barber index's who are available */

    long time        = 0;  /* long ass waits. */
    long barbResult  = 0;  /* current place in line */

    int totalBarbs = 0;    /* total number of barbers for test case */
    int numAvail   = 0;    /* holds the current number of available barbers. */

    GET_DATA(testData);

    do{
        ++time;
        openBarbs = gatherOpenBarbs(barber, time, totalBarbs);
        barbResult = checkForResult(openBarbs);
      }while(barbResult > -1);

    return barbResult;
} /* end findBarbResult */


/* argv[0] == program name, argv[1] == testfile. argc == 2 */
int main(int argc, char *argv[])
{
#define BUF_MAX 4
    FILE *testData = NULL; 

    size_t len     = 0;           /* length of input, not including '\0' */
    int numOfTests = 0;           /* number of tests in the file */

    char buff[BUF_MAX] = {'\0'};  /* buffer to gather number of tests */

    if(argc != 2){noerrExit("Invalid command: $ cmd testfilePath");}

    testData = fopen(argv[1],"r+");
    if(testData == NULL){errExit("main: failure to open test file passed");}

    /* read in number of test cases, convert to int */
    FGETS_NOCLR(buff, BUF_MAX, testData, len);
    numOfTests = getInt(buff, 0, "main: numOfTests");

    /* execute each case */
    do
    {
        findBarbResult(testData);  
        DISP_RESULT();
        --numOfTests;
    }while(numOfTests > 0);

    fclose(testData);

    exit(EXIT_SUCCESS);
}
