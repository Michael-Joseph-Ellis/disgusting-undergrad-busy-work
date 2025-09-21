#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    double a[] = {123.45, 6789.10, -4.0, 6.0, 6.0, 60.0, 6.30};
    double b[] = {124.45, 6790.10, -3.0, 7.0, 7.0, 61.0, 7.30};
    LoopThrough(a,7);
    if (a[0] != b[0] ||
        a[1] != b[1] ||
        a[2] != b[2] ||
        a[3] != b[3] ||
        a[4] != b[4] ||
        a[5] != b[5] ||
        a[6] != b[6])
    {
        std::cout << "expected/correct value for array is {124.45, 6790.10, -3.0, 7.0, 7.0, 61.0, 7.30}, actual value when testing {" <<
                     a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "," << a[4] << "," << a[5] << "," << a[6] << "}.\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}