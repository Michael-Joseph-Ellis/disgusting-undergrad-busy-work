/*************************
 *Michael Ellis*
 *CPSC 2310 Fall 24*
 *mje2*
 *Dr. Yvon Feaster*
*************************/

#include "functions.h"

node_t* createList(FILE* input, node_t** head) {
    node_t* new_node = NULL;

    // !feof(input) - this continues to loop until the end of the file is reached
    while (!feof(input)) {
        new_node = readNodeInfo(input);
        if (new_node != NULL) {
            add(&new_node, head);
        }
    }

    return *head;
}

node_t* readNodeInfo(FILE* input) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // since scanset reads information as a char, i need to first store month, day, and year 
    // as chars and convert them from chars to ints.
    char day_str[3], year_str[5];

    // had problems reading the entire line due to the way csv is formatted and how fgets and 
    // fscanf works so i had to use a buffer here with sscanf to correctly parse from the file 
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), input) == NULL) {
        free(new_node);
        return NULL;
    }

    int fields_read = sscanf(buffer, " %49[^,] , %49[^,] , %9[^,] , %2[^,] , %4[^,] , %9[^,] , %14[^\n]\n",
                             new_node->first_name,
                             new_node->last_name,
                             new_node->birthday.month,
                             day_str,
                             year_str,
                             new_node->major,
                             new_node->communication);

    printf("Fields read: %d\n", fields_read);

    if (fields_read != 7) {
        fprintf(stderr, "Error reading input data. Expected 7 fields but got %d.\n", fields_read);
        free(new_node);
        return NULL;
    }

    new_node->birthday.day = atoi(day_str);
    new_node->birthday.year = atoi(year_str);

    new_node->next = NULL;
    return new_node;
}

void printList(FILE* output, node_t* head) {
    if (head == NULL) {
        fprintf(stderr, "The list is empty.\n");
        return;
    }

    printBorder(output);
    fprintf(output, "LIST INFO:\n\n");

    node_t* temp = head;
    while (temp != NULL) {
        fprintf(output, "Name: %s %s\n", temp->first_name, temp->last_name);
        fprintf(output, "Date of Birth: %s %d, %d\n", 
                temp->birthday.month, temp->birthday.day, temp->birthday.year);
        fprintf(output, "Degree: %s\n", temp->major);
        fprintf(output, "Preferred method of communication: %s\n\n", temp->communication);
        temp = temp->next;
    }

    printBorder(output);
}

void add(node_t** node, node_t** head) {
    if (*head == NULL) {
        *head = *node;
    } else { 
        // traverse through the list until we get to the end
        node_t* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = *node;
    }
}

void printBorder(FILE* output) {
    for (int i = 0; i < 80; i++) {
        fputc('*', output); 
    }
    fputc('\n', output); // dont know if im supposed to do this or not
}

void deleteList(node_t** head) {
    node_t* temp = *head;
    node_t* next_node = NULL;

    while (temp != NULL) {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }

    *head = NULL;
}