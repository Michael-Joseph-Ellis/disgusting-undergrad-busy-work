/*************************
 *Michael Ellis
 *CPSC 2310 Fall 24
 *mje2
 *Dr. Yvon Feaster
 *************************/

#ifndef PPM_H
#define PPM_H

#include <stdio.h>

/**
 * @description Represents a single pixel in an image with RGB color values.
 * 
 * red: The intensity of the red color channel (0-255).
 * green: The intensity of the green color channel (0-255).
 * blue: The intensity of the blue color channel (0-255).
 */
typedef struct {
    unsigned char red;   
    unsigned char green; 
    unsigned char blue;  
} Pixel;

/**
 * @description Represents the header of a PPM file.
 * 
 * format: The PPM format specifier
 * width: The width of the image in pixels.
 * height: The height of the image in pixels.
 * max_color_value: The maximum intensity for each color channel (e.g., 255).
 * 
 * Note: Copied from last lab
 */
typedef struct {
    char format[3];     
    int width;          
    int height;         
    int max_color_value;
} PPMHeader;

/**
 * @description Writes the PPM header to the output file.
 * 
 * @param output_file Pointer to the output file.
 * @param header Pointer to the PPMHeader structure containing header information.
 */
void write_ppm_header(FILE *output_file, const PPMHeader *header);

/**
 * @description Writes a single pixel's RGB values to the output file.
 * 
 * @param output_file Pointer to the output file.
 * @param pixel Pointer to the Pixel structure containing RGB values.
 */
void write_pixel(FILE *output_file, const Pixel *pixel);

#endif