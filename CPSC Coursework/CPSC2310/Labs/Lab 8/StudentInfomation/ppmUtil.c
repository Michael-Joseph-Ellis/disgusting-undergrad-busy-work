/*************************
 *Michael Ellis*
 *CPSC 2310 Fall 24*
 *mje2*
 *Dr. Yvon Feaster*
*************************/

#include "ppmUtil.h"

void readHeader(FILE *inputFile, header_t *header) {
    ignoreComments(inputFile);
    fscanf(inputFile, "%2s", header->type);
    ignoreComments(inputFile);

    while (1) {
        fscanf(inputFile, "%u", &header->width);
        ignoreComments(inputFile);
        if (!feof(inputFile)) break;
    }
    while (1) {
        fscanf(inputFile, "%u", &header->height);
        ignoreComments(inputFile);
        if (!feof(inputFile)) break;
    }

    fscanf(inputFile, "%u", &header->maxVal);
    ignoreComments(inputFile);
}

void readPixels(FILE *inputFile, pixel_t **pixels, unsigned int totalPixels) {
    *pixels = malloc(totalPixels * sizeof(pixel_t));
    if (*pixels == NULL) {
        perror("Unable to allocate memory for pixels");
        exit(EXIT_FAILURE);
    }
    fread(*pixels, sizeof(pixel_t), totalPixels, inputFile);
}

void writeHeader(FILE *outputFile, header_t *header)
{
    fprintf(outputFile, "%s\n%u %u\n%u\n", header->type, header->width, header->height, header->maxVal);
}

void writePixels(FILE *outputFile, pixel_t *pixels, unsigned int totalPixels) {
    fwrite(pixels, sizeof(pixel_t), totalPixels, outputFile);
}

void freePixels(pixel_t *pixels)
{
    free(pixels);
}

void ignoreComments(FILE *inputFile) {
    char c;
    do {
        c = fgetc(inputFile);
        if (c == '#') {
            while (fgetc(inputFile) != '\n');
        } else if (isspace(c)) {
            continue; 
        } else {
            ungetc(c, inputFile);
            break;
        }
    } while (1);
}