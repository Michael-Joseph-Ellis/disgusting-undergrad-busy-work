#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    if (Fibonacci(9) != 34)
    {
        std::cout << "expected/correct value for Fibonacci(9) is 34, actual value when testing " << Fibonacci(9) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}