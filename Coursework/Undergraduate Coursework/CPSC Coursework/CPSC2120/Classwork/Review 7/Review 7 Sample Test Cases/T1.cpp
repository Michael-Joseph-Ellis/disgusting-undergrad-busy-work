#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    if (Fibonacci(1) != 1)
    {
        std::cout << "expected/correct value for Fibonacci(1) is 1, actual value when testing " << Fibonacci(1) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}