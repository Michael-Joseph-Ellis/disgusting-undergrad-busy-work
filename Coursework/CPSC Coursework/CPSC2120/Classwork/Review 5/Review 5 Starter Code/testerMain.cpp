#include "review.h"

int main() {
    std::cout << "Enter the size of the array: ";
    int size;
    std::cin >> size;

    std::vector<int> array = InitializeArray(size);

    std::cout << "Initialized array: ";
    for (int value : array) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
