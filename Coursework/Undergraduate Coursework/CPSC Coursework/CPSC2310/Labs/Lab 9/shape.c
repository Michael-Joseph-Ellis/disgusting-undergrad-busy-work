/*************************
 *Michael Ellis
 *CPSC 2310 Fall 24
 *mje2
 *Dr. Yvon Feaster
 *************************/

#include "shape.h"
#include <stdio.h>
#include <math.h>

void read_circle_data(FILE *input_file, PPMHeader *header, Circle *circle)
{
    if (input_file == NULL || header == NULL || circle == NULL) 
    {
        fprintf(stderr, "Error: Null pointer passed to read_circle_data.\n");
        return;
    }

    // Read the PPM header
    fscanf(input_file, "%s %d %d %d", header->format, &header->width, &header->height, &header->max_color_value);

    // Read circle center, radius, and color
    fscanf(input_file, "%d %d %d", &circle->center.x, &circle->center.y, &circle->radius);

    // Read RGB color values as integers and directly assign after validation
    int red, green, blue;
    fscanf(input_file, "%d %d %d", &red, &green, &blue);
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) {
        fprintf(stderr, "Error: Invalid RGB value in input file.\n");
        return;
    }
    circle->color.red = (unsigned char)red;
    circle->color.green = (unsigned char)green;
    circle->color.blue = (unsigned char)blue;
}

/**
 * Purposely avoiding using sqrt implementation because while the formula given is correct, 
 * this implementation is computationally less expensive and more efficient. The square root itself is not necessary. 
 */
int is_pixel_in_circle(int x, int y, const Circle *circle) 
{
    // Print error message and return 0 if circle pointer is null
    if (circle == NULL) 
    {
        fprintf(stderr, "Error: Null pointer passed to is_pixel_in_circle.\n");
        return 0;
    }
    
    // Calculate the distance from the center of the circle to the pixel
    int dx = x - circle->center.x;
    int dy = y - circle->center.y;
    return (dx * dx + dy * dy) <= (circle->radius * circle->radius);
}

void draw_circle(FILE *output_file, const PPMHeader *header, const Circle *circle, const Pixel *bg_color) 
{
    // Print error message and return if any pointer is null
    if (output_file == NULL || header == NULL || circle == NULL || bg_color == NULL) 
    {
        fprintf(stderr, "Error: Null pointer passed to draw_circle.\n");
        return;
    }

    // Iterate through each pixel in the image
    for (int y = 0; y < header->height; ++y) 
    {
        for (int x = 0; x < header->width; ++x) 
        {
            Pixel pixel = is_pixel_in_circle(x, y, circle) ? circle->color : *bg_color;
            fwrite(&pixel, sizeof(Pixel), 1, output_file);
        }
    }
}