#include "review.h"

int main() {
    // Test with a string
    int result1 = WriteOut("Hello, world!");
    std::cout << "Returned: " << result1 << std::endl;

    // Test with an integer
    int result2 = WriteOut(42);
    std::cout << "Returned: " << result2 << std::endl;

    // Test with a double
    int result3 = WriteOut(3.14);
    std::cout << "Returned: " << result3 << std::endl;

    return 0;
}
