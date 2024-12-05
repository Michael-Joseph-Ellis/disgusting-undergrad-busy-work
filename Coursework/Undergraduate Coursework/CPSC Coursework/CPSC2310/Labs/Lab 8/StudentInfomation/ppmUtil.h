/*************************
 *Michael Ellis*
 *CPSC 2310 Fall 24*
 *mje2*
 *Dr. Yvon Feaster*
*************************/

#ifndef PPMUTIL_H
#define PPMUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Pixel
{
    unsigned char r, g, b;
}pixel_t;

typedef struct Header
{
    char type[3];
    unsigned int width;
    unsigned int height;
    unsigned int maxVal;
}header_t;

//Your function prototypes will placed here.
void readHeader(FILE *img, header_t *header);
void readPixels(FILE *inputFile, pixel_t **pixels, unsigned int totalPixels);
void writeHeader(FILE *outputFile, header_t *header);
void writePixels(FILE *outputFile, pixel_t *pixels, unsigned int totalPixels);
void ignoreComments(FILE *inputFile);
void freePixels(pixel_t *pixels);

#endif