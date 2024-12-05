/*************************
 *Michael Ellis*
 *CPSC 2310 Fall 24*
 *mje2*
 *Dr. Yvon Feaster*
*************************/

#include "functions.h"

int main(int argc, char* argv[]) {
    assert(argc == 3 && "Usage: ./program_name <input_file> <output_file>");

    FILE* input = fopen(argv[1], "r");
    assert(input != NULL && "Not opened correctly.");

    FILE* output = fopen(argv[2], "w");
    assert(output != NULL && "Error opening output file");

    // initializing the head of linked list as NULL
    node_t* head = NULL;

    // head = createList(input, &head);
    
    printList(output, createList(input, &head));

    deleteList(&head);
    fclose(input);
    fclose(output);

    return 0;
}