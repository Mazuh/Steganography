/**
 * @author Mazuh
 * @brief Portable PixMap (.ppm) image handler
 */

#include <stdio.h>
#include "ppm.h"

void _ppm_read(const char *filename){
    //PPM image;

    FILE *img_file = fopen(filename, "rb");

    // seek file size in bytes
    unsigned long size;
    fseek(img_file, 0, SEEK_END);
    size = ftell(img_file);
    fseek(img_file, 0, SEEK_SET);

    // confirm type
    char type[3];
    fscanf(img_file, " %s ", type);

    if (!(type[0] == 'P' || type[1] == '6')){
        printf("Invalid file.\n");
        return;
    }

    // read image dimensions
    unsigned int width, height;
    fscanf(img_file, " %u %u ", &width, &height);

    // read max color value
    unsigned int max_color;
    fscanf(img_file, " %u ", &max_color);

    // print the whole header
    printf("File: %s\nSize: %lumb, Type: %s, Width: %u, Height: %u\n", filename, size/1048576, type, width, height);

    // now read the image pixels
    unsigned char r, g, b;
    //Pixel px;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            fscanf(img_file, " %c%c%c ", &r, &g, &b);
        }
    }
    
    fclose(img_file);
}

