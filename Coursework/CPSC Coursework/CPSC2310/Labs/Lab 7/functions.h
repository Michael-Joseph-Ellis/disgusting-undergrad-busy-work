/*************************
 *Michael Ellis*
 *CPSC 2310 Fall 24*
 *mje2*
 *Dr. Yvon Feaster*
*************************/
// File: functions.h
// Function Prototypes, declaration of structs, and all #includes.

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Structs 

// Struct to represent the birthday of the student 
typedef struct {
    char month[10];
    int day;
    int year;
} birthday_t;

// Struct to represent a node in the linked list 
typedef struct node {
    char first_name[50];
    char last_name[50];
    char major[50];
    char communication[15];
    birthday_t birthday;
    struct node* next;
} node_t;

// Function Prototypes

/*
    * @brief Creates a linked list from the input file.
    * 
    * @param input The input file pointer.
    * @param head A double pointer to the head of the linked list.
    * 
    * @return A pointer to the head of the linked list.
*/
node_t* createList(FILE*, node_t**);

/*
    * @brief Reads node information from the input file.
    * 
    * @param input The input file pointer.
    * @return A pointer to the newly created node with populated data.
*/
node_t* readNodeInfo(FILE* input);

/*
    * @brief Adds a node to the linked list.
    * 
    * @param node A double pointer to the node being added.
    * @param head A double pointer to the head of the linked list.
*/
void add(node_t** node, node_t** head);

/*
    * @brief Prints the entire linked list to the output file.
    * 
    * @param output The output file pointer.
    * @param head The head of the linked list.
*/
void printList(FILE*, node_t*);

/*
    * @brief Prints a border of 80 asterisks to the output file.
    * 
    * @param output The output file pointer.
*/
void printBorder(FILE*);


/*
    * @brief Frees the memory allocated for the linked list.
    * 
    * @param head A double pointer to the head of the linked list.
*/
void deleteList(node_t**);

#endif // FUNCTIONS_H