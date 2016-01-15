#include <stdio.h>
#include <stdlib.h>


int main()
{
  //get numCases
  long numCases;
  scanf("%ld", &numCases);


  long n = 0;
  for(n=0;n<numCases;n++)
  {

      //get numBarbs
      long numBarbs;
      scanf("%ld", &numBarbs);

      //get pos -> N
      long N;
      scanf("%ld", &N);
      N -= numBarbs;
      if(N <= 0)
      {
        printf("ans: %ld\n", numBarbs+N);
      }

      long OT[numBarbs]; //barber haircut times
      long CS[numBarbs]; //current time state info

      //reading in barber times
      long k = 0;
      for(k=0;k<numBarbs;k++)
      {
        scanf("%ld", &OT[k]);
        
        //intializing current time info
        CS[k]=OT[k];
      }

      long min;
      long mindex = 0;

      long i = 0;
      while(i < N)
      {
        long j;
        min = CS[0];
        mindex = 0;

        for(j=1; j < numBarbs; j++)
        {
          if(CS[j] < min)
          {
            min = CS[j];
            mindex = j;
          }
      }

      for(k=0;k<numBarbs;k++)
      {
        CS[k] -= min;
      }
      
      CS[mindex] = OT[mindex];
      i++;
  
    }

      mindex++;
      printf("ans: %ld\n", mindex);

  }

  return 0;
}
