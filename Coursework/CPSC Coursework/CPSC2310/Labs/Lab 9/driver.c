/*************************
 *Michael Ellis
 *CPSC 2310 Fall 24
 *mje2
 *Dr. Yvon Feaster
 *************************/

#include "ppm.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv) {
    // Ensure correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the input and output files
    FILE *input_file = fopen(argv[1], "r");
    assert(input_file && "Error: Unable to open input file.");

    FILE *output_file = fopen(argv[2], "wb");
    assert(output_file && "Error: Unable to open output file.");

    // Read the header and circle data from the input file
    PPMHeader header;
    Circle circle;
    read_circle_data(input_file, &header, &circle);

    // Write the PPM header to the output file
    write_ppm_header(output_file, &header);

    // Define the background color
    Pixel bg_color = {102, 0, 204}; // Purple background color to try and recreate the image in the docx

    // Create the circle in the PPM image
    draw_circle(output_file, &header, &circle, &bg_color);

    // Close the files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
