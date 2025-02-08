#include <iostream>
#include <vector>
#include "review.h"

using namespace std;

int main()
{
    if (Fibonacci(16) != 987)
    {
        std::cout << "expected/correct value for Fibonacci(16) is 987, actual value when testing " << Fibonacci(16) << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}