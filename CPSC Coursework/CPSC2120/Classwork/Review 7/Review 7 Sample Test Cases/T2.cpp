#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    if (Fibonacci(4) != 3)
    {
        std::cout << "expected/correct value for Fibonacci(4) is 3, actual value when testing " << Fibonacci(4) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}