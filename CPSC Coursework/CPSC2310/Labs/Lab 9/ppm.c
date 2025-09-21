/*************************
 *Michael Ellis
 *CPSC 2310 Fall 24
 *mje2
 *Dr. Yvon Feaster
 *************************/

#include "ppm.h"
#include <stdio.h>

void write_ppm_header(FILE *output_file, const PPMHeader *header) 
{
    // Check for null pointers
    if (output_file == NULL || header == NULL)
    {
        // Print error message and return if any pointer is null
        fprintf(stderr, "Error: Null file or header pointer passed to write_ppm_header.\n");
        return;
    }

    // Write the PPM header to the output file
    fprintf(output_file, "%s\n%d %d\n%d\n", header->format, header->width, header->height, header->max_color_value);
}

void write_pixel(FILE *output_file, const Pixel *pixel)
{
    // Check for null pointers
    if (output_file == NULL || pixel == NULL) 
    { 
        // Print error message and return if any pointer is null
        fprintf(stderr, "Error: Null file or pixel pointer passed to write_pixel.\n");
        return;
    }

    // Write the pixel's RGB values to the output file
    fwrite(&(pixel->red), sizeof(unsigned char), 1, output_file);
    fwrite(&(pixel->green), sizeof(unsigned char), 1, output_file);
    fwrite(&(pixel->blue), sizeof(unsigned char), 1, output_file);
}