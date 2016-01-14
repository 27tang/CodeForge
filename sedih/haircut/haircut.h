/* header for haircut program */

/* what a barber actually is in the eyes of the computer */
typedef struct barber
{
    int barbNum;
    int cutSpeed;
} barb_s;

/* finds a list of available barbers */

/* returns the barber with the lowest number from an array of pointers to
   barbers */

/* fills all currently open barber chairs FROM ARRAY OF FREE chairs.
   NOTE: Should not be used if N will be placed in a barber chair. Only when
         the filling order will not matter. */

