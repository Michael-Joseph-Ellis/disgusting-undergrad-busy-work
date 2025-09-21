#include "review.h"

void ReadStdIn() {
    int intValue;
    double doubleValue;
    std::string stringValue;

    std::cin >> intValue >> doubleValue >> stringValue;

    std::cout << intValue << std::endl;
    std::cout << doubleValue << std::endl;
    std::cout << stringValue << std::endl;
}
