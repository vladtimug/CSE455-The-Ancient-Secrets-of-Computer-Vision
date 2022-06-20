#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

/**
 * @brief Get pixel value located at column x, row y and channel c
 * 
 * @param im Image object
 * @param x Image column index
 * @param y Image row index
 * @param c Image channel index
 * @return float 
 */
float get_pixel(image im, int x, int y, int c)
{
    // Use clamping pad strategy to avoid indexing image data at invalid values
    if(x < 0) {
        x = 0;
    } else if(x > im.w) {
        x = im.w - 1;
    }

    if(y < 0) {
        y = 0;
    } else if(y > im.h) {
        y = im.h - 1;
    }

    if(c < 0) {
        c = 0;
    } else if(c > im.c) {
        c = im.c - 1;
    }

    int pixel_position = x + y * im.w + c*im.w*im.h;
    
    return im.data[pixel_position];
}

/**
 * @brief Set the pixel value located at column x, row y and channel c to value v
 * 
 * @param im Image object
 * @param x Image column index
 * @param y Image row index
 * @param c Image channel index
 * @param v New pixel value
 */
void set_pixel(image im, int x, int y, int c, float v)
{
    if ((x >= 0 && x < im.w) && (y >=0 && y < im.h) && (c >= 0 && c < im.c)) {
        int pixel_position = x + y * im.w + c*im.w*im.h;
        im.data[pixel_position] = v;
    }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
}

void clamp_image(image im)
{
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
