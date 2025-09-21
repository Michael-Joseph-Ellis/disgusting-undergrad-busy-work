#include <iostream>
#include "review.h"

int main()
{
    if (WriteOut(123) != 2)
    {
        std::cout << "expected/correct value for WriteOut(123) is 2, actual value when testing " << WriteOut(123) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}