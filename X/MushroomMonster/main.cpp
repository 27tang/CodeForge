#include <bits/stdc++.h>
using namespace std;

int main()
{
  int numOfCases = 0;
  cin >> numOfCases; cin.ignore();
  
  for(int i = 0; i < numOfCases; ++i)
  {
    int numOfIntervals = 0;
    cin >> numOfIntervals; cin.ignore();
    int array[numOfIntervals];

    for(int j = 0; j < numOfIntervals; ++j)
    {
      cin >> array[j]; cin.ignore();
    }  

    int mushroomsEaten = 0;
    for(int j = 1; j < numOfIntervals; ++j)
    {
      if(array[j-1] > array[j])
        mushroomsEaten += array[j-1] - array[j];
    }

    int mushroomsEaten2 = 0;
    if(numOfIntervals > 1)
    {
      int maxDiff = 0;
      for(int j = 1; j < numOfIntervals; ++j)
      {
        if((array[j-1] > array[j]) && array[j-1] - array[j] > maxDiff)
          maxDiff = array[j-1] - array[j];
      }
      //cout << "MAXDIFF : " << maxDiff << endl;
      for(int j = 0; j < numOfIntervals-1; ++j)
      {
        if(array[j] <= maxDiff)
          mushroomsEaten2 += array[j];
        else
          mushroomsEaten2 += maxDiff;
      }
    }
    cout << "Case #" << i +1 << ": " << mushroomsEaten << " " << mushroomsEaten2 <<  endl;
  }
  return 0;
}
