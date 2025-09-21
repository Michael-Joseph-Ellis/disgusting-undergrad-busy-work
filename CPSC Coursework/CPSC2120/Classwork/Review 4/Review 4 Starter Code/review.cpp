#include "review.h"
#include <iostream>
#include <string>

void ReadWrite() {
    std::string input;
    std::string result;

    while (std::cin >> input) {
        if (input == "q") {
            break;
        }
        if (!result.empty()) {
            result += " ";
        }
        result += input;
    }

    result += " ";

    std::cout << result << std::endl;
}
