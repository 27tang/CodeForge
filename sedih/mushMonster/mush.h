/* header for the mush problem */

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
int gather_results(int *result[]);
/* print the results of each method */
void display_results(int *result[], int numTests);
