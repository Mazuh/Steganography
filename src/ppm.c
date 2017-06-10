/**
 * @author Mazuh
 * @brief Portable PixMap (.ppm) image handler
 */

#include <stdio.h>
#include "ppm.h"

PPM image;

PPM *ppm_read(const char *filename){

    // open it!
    FILE *img_file = fopen(filename, "rb");

    // seek file size in bytes
    fseek(img_file, 0, SEEK_END);
    image.size = ftell(img_file);
    fseek(img_file, 0, SEEK_SET);

    // confirm type
    char type[3];
    fscanf(img_file, " %s ", type);

    if (!(type[0] == 'P' || type[1] == '6')){
        printf("Invalid file.\n");
        return;
    }

    // read image dimensions
    fscanf(img_file, " %u %u ", &image.width, &image.height);

    // read max color value
    fscanf(img_file, " %hhu ", &image.max_color);

    // print the whole header
    printf("File: %s\nSize: %lumb, Type: %s, Width: %u, Height: %u\n", filename, image.size/1048576, type, image.width, image.height);

    // now read the image pixels
    Pixel pixel;
    char r, g, b;

    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){
            fscanf(img_file, " %c%c%c ", &r, &g, &b);
            pixel.red = (unsigned char) r;
            pixel.green = (unsigned char) g;
            pixel.blue = (unsigned char) b;
            image.pixel_map[i][j] = pixel;
        }
    }

    // bye
    fclose(img_file);

    return &image;
}

