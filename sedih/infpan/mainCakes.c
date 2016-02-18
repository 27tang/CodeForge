#define __SED_ERR__
#define __SED__NUM__
#include "../sed/sedhead.h"

int main(int argc, char* argv[])
{
    FILE *inData = NULL;

    if(argc != 2){ 
        noerrExit("main: Invalid number of arguments: cmdName testFile");}

    if(fopen(argv[1],"r+") == NULL){
        errExit("main: Failure to open testfile from argv");}


    fclose(inData);
    exit(EXIT_SUCCESS);
}
