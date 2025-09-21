#include <iostream>
#include "review.h"

int main()
{
    if (WriteOut(3.1415926535) != 3)
    {
        std::cout << "expected/correct value for WriteOut(3.1415926535) is 3, actual value when testing " << WriteOut(3.1415926535) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}