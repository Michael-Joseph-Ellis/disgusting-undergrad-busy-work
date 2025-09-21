#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    double a[] = {1.0,2.0,3.0};
    double b[] = {2.0,3.0,4.0};
    LoopThrough(a,3);
    if (a[0] != b[0] ||
        a[1] != b[1] ||
        a[2] != b[2])
    {
        std::cout << "expected/correct value for array is {2.0,3.0,4.0}, actual value when testing {" <<
                     a[0] << "," << a[1] << "," << a[2] << "}.\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}