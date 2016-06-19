#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;


int main(int argc, char *argv[])
{
    ifstream in_file;
    in_file.open(argv[1]);

    int num_cases = 0;
    int num_plates = 0;
    int * plates = NULL;
    int cur_case = 1;
    int case_total = 0;
    int diff = 0;
    int largest_diff = 0;
    float mcr = 0.0;
    int case_total2 = 0;

    if(in_file)
    {
        in_file >> num_cases;
        in_file.ignore(100, '\n');
        while(num_cases > 0)
        {
            in_file >> num_plates;
            in_file.ignore(100, '\n');
            plates = new int[num_plates];

            for(int i = 0; i < num_plates; ++i)
            {
                in_file >> plates[i];
            }

            in_file.ignore(100, '\n');

            for(int i = 0; i < (num_plates - 1); ++i)
            {
                if(plates[i] > plates[i+1])
                {   
                    diff = abs(plates[i] - plates[i+1]);
                    case_total += diff;
                }
                if(diff > largest_diff)
                {
                    largest_diff = diff;
                }
            }

            for(int i = 0; i < num_plates; ++i)
            {
                if((plates[i] - largest_diff) <= 0)
                    case_total2 += plates[i];
                else
                    case_total2 += (plates[i] - largest_diff);
            }
           
            
            
            cout << "Case #" << cur_case++ <<"\t" << case_total << "\t" << case_total2 << endl;

            delete [] plates;
            case_total = case_total2 = 0;
            --num_cases;
        }
    }
    else
        cout << "wtf happened" << endl;
    


    return 0;
}
