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

/**
 * @brief Make a copy of an image and return it
 * 
 * @param im 
 * @return image 
 */
image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    copy.data = im.data;
    return copy;
}

/**
 * @brief Convert image from RGB to Grayscale colorspace
 * 
 * @param im 
 * @return image 
 */
image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    
    for(int x_coordinate = 0; x_coordinate < im.w; x_coordinate++)
    {
        for(int y_coordinate = 0; y_coordinate < im.h; y_coordinate++)
        {
            float red_pixel_value = get_pixel(im, x_coordinate, y_coordinate, 0);
            float green_pixel_value = get_pixel(im, x_coordinate, y_coordinate, 1);
            float blue_pixel_value = get_pixel(im, x_coordinate, y_coordinate, 2);
            float gray_pixel_value = 0.299 * red_pixel_value + 0.587 * green_pixel_value + 0.114 * blue_pixel_value;
            set_pixel(gray, x_coordinate, y_coordinate, 0, gray_pixel_value);
        }
    }
    return gray;
}

/**
 * @brief Shift pixel values in image by the given amount without clamping
 * 
 * @param im 
 * @param c 
 * @param v 
 */
void shift_image(image im, int c, float v)
{
    for(int x_coordinate = 0; x_coordinate < im.w; x_coordinate++)
    {
        for(int y_coordinate = 0; y_coordinate < im.h; y_coordinate++)
        {
            float old_pixel_value = get_pixel(im, x_coordinate, y_coordinate, c);
            float new_pixel_value = old_pixel_value  + v;
            set_pixel(im, x_coordinate, y_coordinate, c, new_pixel_value);
        }
    }
}

/**
 * @brief Clamp image pixel values to avoid byte overflow
 * 
 * @param im 
 */
void clamp_image(image im)
{
    for(int x_coordinate = 0; x_coordinate < im.w; x_coordinate++)
    {
        for(int y_coordinate = 0; y_coordinate < im.h; y_coordinate++)
        {
            for(int z_coordinate = 0; z_coordinate < im.c; z_coordinate++)
            {
                float pixel_value = get_pixel(im, x_coordinate, y_coordinate, z_coordinate);
                if(pixel_value < 0)
                    set_pixel(im, x_coordinate, y_coordinate, z_coordinate, 0);
                else if(pixel_value > 1)
                    set_pixel(im, x_coordinate, y_coordinate, z_coordinate, 1);
            }
        }
    }
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
