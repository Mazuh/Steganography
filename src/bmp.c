/**
 * @author Mazuh
 * @brief Bitmap (.bmp) image handler
 */

#include <stdio.h>
#include <string.h>

#include "bmp.h"

BMP _image;

void bmp_encode(const char *filename, const char *message){
    _bmp_read_from_file(filename, 0);
}

void _bmp_read_from_file(const char *filename, int secret){

    // open it!
    FILE *img_file = fopen(filename, "rb");

    // TODO

    // bye
    fclose(img_file);
}
