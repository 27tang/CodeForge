#define __SED_ERR__
#define __SED_NUM__
#define __SED_LINUX__
#include "../sed/sedhead.h" /* my header */
#include "haircut.h"


/* argv[0] == program name, argv[1] == testfile. argc == 2 */
int main(int argc, char *argv[])
{
    FILE *testData = NULL;

    if(argc != 2){noerrExit("Invalid command: $ cmd testfilePath");}

    testData = fopen(argv[1],"r+");
    if(testData == NULL){errExit("main: failure to open test file passed");}
    
     

    fclose(testData);
}
