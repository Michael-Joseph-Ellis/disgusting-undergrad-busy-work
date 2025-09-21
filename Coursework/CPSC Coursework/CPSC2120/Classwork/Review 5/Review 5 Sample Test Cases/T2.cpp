#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    int array_0[] = {0,0,0,0,0,0,0,0,0,0};
    vector<int> a;
    a = InitializeArray(10);
    int * b = &a[0];
    if (array_0[0] != b[0] ||
        array_0[1] != b[1] ||
        array_0[2] != b[2] ||
        array_0[3] != b[3] ||
        array_0[4] != b[4] ||
        array_0[5] != b[5] ||
        array_0[6] != b[6] ||
        array_0[7] != b[7] ||
        array_0[8] != b[8] ||
        array_0[9] != b[9])
    {
        std::cout << "expected/correct value for array is {0,0,0,0,0,0,0,0,0,0}, actual value when testing {" <<
                     b[0] << "," << b[1] << "," << b[2] << "," << b[3] << "," << b[4] << "," <<
                     b[5] << "," << b[6] << "," << b[7] << "," << b[8] << "," << b[9] << "}.\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}