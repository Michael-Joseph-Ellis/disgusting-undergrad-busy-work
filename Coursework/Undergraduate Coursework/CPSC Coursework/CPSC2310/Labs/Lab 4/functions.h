/**************************
* Michael Joseph Ellis *
* CPSC2310 Fall 2024 *
* UserName: mje2 *
* Instructor: Dr. Yvon Feaster *
*************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** readFile(FILE* fp, int *size);
void printMatrix (int** mat, int num);
int calculateVal(int** mat, int size);
bool isRightDiagonal(int size, int row, int col);
bool isLeftDiagonal(int size, int row, int col);