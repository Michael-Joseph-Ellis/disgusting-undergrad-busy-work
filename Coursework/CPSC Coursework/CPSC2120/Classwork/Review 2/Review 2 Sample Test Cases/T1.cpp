#include <iostream>
#include "review2.h"

int main()
{
    if (WriteOut("This is a string") != 1)
    {
        std::cout << "expected/correct value for WriteOut(\"This is a string\") is 1, actual value when testing " << WriteOut("This is a string") << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}