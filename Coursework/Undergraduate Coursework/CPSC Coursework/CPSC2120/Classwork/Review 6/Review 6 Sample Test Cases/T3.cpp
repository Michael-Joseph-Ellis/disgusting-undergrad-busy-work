#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    double a[] = {1};
    double b[] = {2};
    LoopThrough(a,1);
    if (a[0] != b[0])
    {
        std::cout << "expected/correct value for array is {2}, actual value when testing {" <<
                     a[0] << "}.\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}