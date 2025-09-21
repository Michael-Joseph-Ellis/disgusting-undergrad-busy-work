#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    if (Fibonacci(7) != 13)
    {
        std::cout << "expected/correct value for Fibonacci(7) is 13, actual value when testing " << Fibonacci(7) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}