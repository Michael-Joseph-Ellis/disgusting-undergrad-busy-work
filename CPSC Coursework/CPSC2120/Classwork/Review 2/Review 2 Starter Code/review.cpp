#include "review.h"

int WriteOut(std::string output) {
    std::cout << output << std::endl;
    return 1; // Return 1 for strings
}

int WriteOut(int output) {
    std::cout << output << std::endl;
    return 2; // Return 2 for integers
}

int WriteOut(double output) {
    std::cout << output << std::endl;
    return 3; // Return 3 for doubles
}
