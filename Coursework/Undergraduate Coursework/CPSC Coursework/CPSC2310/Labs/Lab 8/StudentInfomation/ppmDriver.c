/*************************
 *Michael Ellis*
 *CPSC 2310 Fall 24*
 *mje2*
 *Dr. Yvon Feaster*
*************************/

#include "ppmUtil.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.ppm> <output.ppm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen(argv[2], "wb");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    header_t header;
    pixel_t *pixels;
    unsigned int totalPixels;

    readHeader(inputFile, &header);

    totalPixels = header.width * header.height;
    readPixels(inputFile, &pixels, totalPixels);

    writeHeader(outputFile, &header);
    writePixels(outputFile, pixels, totalPixels);

    freePixels(pixels);
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}