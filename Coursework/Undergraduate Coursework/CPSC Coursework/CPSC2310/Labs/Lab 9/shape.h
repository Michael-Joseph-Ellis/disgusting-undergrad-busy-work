/*************************
 *Michael Ellis
 *CPSC 2310 Fall 24
 *mje2
 *Dr. Yvon Feaster
 *************************/

#ifndef SHAPE_H
#define SHAPE_H

#include "ppm.h"

/**
 * @description Represents a point in 2D space with integer coordinates.
 * 
 * x: The horizontal coordinate.
 * y: The vertical coordinate.
 */
typedef struct {
    int x; 
    int y;
} Point;

/**
 * @description Represents a circle defined by its center, radius, and color.
 * 
 * center: A `Point` struct representing the center of the circle.
 * radius: An integer representing the radius of the circle in pixels.
 * color: A `Pixel` struct defining the RGB color of the circle.
 */
typedef struct {
    Point center;
    int radius;   
    Pixel color; 
} Circle; 

/**
 * @description Reads circle information from the input file, including header, center point, radius, and color.
 * 
 * @param input_file Pointer to the input file containing circle data.
 * @param header Pointer to the PPMHeader structure to store header information.
 * @param circle Pointer to the Circle structure to store circle data.
 */
void read_circle_data(FILE *input_file, PPMHeader *header, Circle *circle);

/**
 * @description Checks whether a pixel at a given location is within a circle.
 * 
 * @param x The X-coordinate of the pixel.
 * @param y The Y-coordinate of the pixel.
 * @param circle Pointer to the Circle structure describing the circle.
 * @return int Returns 1 if the pixel is inside the circle, 0 otherwise.
 */
int is_pixel_in_circle(int x, int y, const Circle *circle);

/**
 * @description Loops through each pixel in the image, checking if it lies within the circle.
 *        Assigns the appropriate color (circle color or background color) and writes the pixel to the output file.
 * 
 * @param output_file Pointer to the output file.
 * @param header Pointer to the PPMHeader structure containing image dimensions.
 * @param circle Pointer to the Circle structure describing the circle.
 * @param bg_color Pointer to the Pixel structure representing the default background color.
 */
void draw_circle(FILE *output_file, const PPMHeader *header, const Circle *circle, const Pixel *bg_color);

#endif 