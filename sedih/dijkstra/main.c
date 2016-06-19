#define __SED_LINUX__
#include "../sed/sedhead.h"
#include "../sed/err_handle/err_handle.h"

char** allocateTable();

int main(int argc, char *argv[])
{
    char **identityTable = NULL;

    // allocate table
    identityTable = allocateTable();

} // end main

char** allocateTable(){ // talk about overkill #{{{
#define TBLSIZE 4
#define COLSIZE 4
#define ROWSIZE 4
#define INSIZE  2
#define DATAIN  75 
    char *dataBuff = NULL;  // date pulled from file
    char *bfPl     = NULL;  // place in buffer
    char *toInsert = NULL;  // data pulled from buffer 
    char **identityTable = NULL;
    int fdTable = 0;            // file descriptor for table matrix
    int i = 0;
    int p = 0;
    size_t nByte = DATAIN;      // nBytes to read, including room from '\0'

    // allocate pointers
    identityTable = (char**) malloc(sizeof(char*)*TBLSIZE);

    // allocate initial row (representing column identification
    identityTable[0] = (char*) malloc(sizeof(char)*COLSIZE);

    // allocate remaining rows
    for(i=1; i < TBLSIZE; ++i){
        identityTable[i] = (char*) malloc(sizeof(char)*ROWSIZE);
    } // end for

    // set table data
    dataBuff = (char*) malloc(sizeof(char)*DATAIN);

    if((fdTable = open("testfiles/tableMatrix.in", O_RDONLY)) == -1){
        errExit("allocateTable: fdTable open() failure");
    } // end if
    
    // read in table
    READ_INPUT(fdTable, dataBuff, nByte);
    
    // fill table
    bfPl = dataBuff;
    for(i=0; i < COLSIZE; ++i){
        toInsert = (char*) malloc(sizeof(char)*INSIZE);
        READ_NEXT_FILE(fdTable, dataBuff, bfPl, nByte, toInsert,
                       *bfPl != ',' && *bfPl != '\n');
        identityTable[0][i] = *toInsert; // first row will never have '-'
    } // end for 
    
    for(p = 1; p < TBLSIZE; ++p){
        for(i=0; i < ROWSIZE; ++i){
            toInsert = (char*) malloc(sizeof(char)*INSIZE);
            READ_NEXT_FILE(fdTable, dataBuff, bfPl, nByte, toInsert,
                           *bfPl != ',' && *bfPl != '\n');
            identityTable[p][i] = *toInsert;
            if(*toInsert == '-'){ // if the character was negetive
                identityTable[p][i] = toInsert[1];
            } // end if 
        } // end for
    } // end for 
    
    return identityTable;
///#{{{ undefine
#undef TBLSIZE
#undef COLSIZE
#undef ROWSIZE
#undef INSIZE
#undef DATAIN
//}}}#/
} // end allocateTable }}}#

