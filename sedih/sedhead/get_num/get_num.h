/*
    file: get_num.h
    
    Turns a string of characters into a their numerical equivilance using
    strtoul, and error checking the results.

    referenced from linux programming interface handbook.
*/

#ifndef _GET_NUM_H
#define _GET_NUM_H
                    /* definitions */
#define GN_NONEG    0x1      /* Value must be >= 0 */
#define GN_GT_O     0x2      /* Value must be > 0  */

                            /* By default base is passed in as 0 (strtol(3)) */
#define GN_BASE_10  0x4     /* Value is expressed in decimal */
#define GN_BASE_8   0x8     /* Value is expressed in octal */
#define GN_BASE_16  0x16    /* Value is expressed in hexadecimal */

                            /* By default, process uses exit() on error */
#define GN_NOEXIT_  0x32    /* Return 0, set errno on conversion error */

#include <sys/types.h>
#include <inttypes.h>

/* ERROR HANDLE NOTE: If using the GN_NOEXIT_ flag, error is checked when
   function returns a 0 AND arg != '0' */

                    /* public prototypes */

/* turn arg into a long based on flags. name used in error message */
long getLong(const char *arg, int flags, const char *varName);

/* turn arg into a int based on flags. name used in error message */
int getInt(const char *arg, int flags, const char *varName);

/* turn arg into a int32_t based on flags. name used in error message */
int32_t get32_t(const char *arg, int32_t flags, const char *varName);

/* turn arg into a int64_t based on flags. name used in error message */
int64_t get64_t(const char *arg, int32_t flags, const char *varName);

/* turn arg into a uint32_t based on flags. name used in error message */
uint32_t getu32_t(const char *arg, int32_t flags, const char *varName);

/* turn arg into a uint64_t based on flags. name used in error message */
uint64_t getu64_t(const char *arg, int32_t flags, const char *varName);
#endif
