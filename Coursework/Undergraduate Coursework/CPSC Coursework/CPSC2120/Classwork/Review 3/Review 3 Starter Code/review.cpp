#include "review.h"

void ReadStdIn2() {
    std::string input;
    int count = 0;

    while (true){
        std::cin >>input;

        if (input == "q"){
            break;
        }

        count++;
    }

    std::cout<<count<<std::endl;
}