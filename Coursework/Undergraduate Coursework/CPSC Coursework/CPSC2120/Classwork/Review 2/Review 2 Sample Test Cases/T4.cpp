#include <iostream>
#include "review.h"

int main()
{
    if (WriteOut(0) != 2)
    {
        std::cout << "expected/correct value for WriteOut(0) is 2, actual value when testing " << WriteOut(0) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}