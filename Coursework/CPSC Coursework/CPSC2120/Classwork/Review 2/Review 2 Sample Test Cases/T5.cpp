#include <iostream>
#include "review.h"

int main()
{
    if (WriteOut(1.23) != 3)
    {
        std::cout << "expected/correct value for WriteOut(1.23) is 3, actual value when testing " << WriteOut(1.23) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}