#include <iostream>
#include "review.h"

int main()
{
    if (WriteOut("My mistress' eyes are nothing like the sun") != 1)
    {
        std::cout << "expected/correct value for WriteOut(\"My mistress' eyes are nothing like the sun\") is 1, actual value when testing " << WriteOut("My mistress' eyes are nothing like the sun") << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}