/**************************
* Michael Joseph Ellis *
* CPSC2310 Fall 2024 *
* UserName: mje2 *
* Instructor: Dr. Yvon Feaster *
*************************/


#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char** argv)
{
    printf("checking command line arguments\n");

    if (argc < 2)
    { 
        printf("not enough argument: ./exe filename\n"); 
        exit(-1);
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("fp did not open\n"); 
        exit(-1);
    }

    int size = 0;
    int **mat = readFile(fp, &size);
    printMatrix(mat, size);

    int total = calculateVal(mat, size);
    printf("The total sum excluding diagonals is: %d\n", total);

    for (int i = 0; i < size; i++) {
        free(mat[i]);
    }
    free(mat); 

    fclose(fp);

    return 0;
}
