/**
 * @author Mazuh
 * @brief Bitmap (.bmp) image handler
 */

#include <stdio.h>
#include <string.h>

#include "bmp.h"

const char BMP_DEFAULT_ASSET_FILENAME[] = "./default_assets/imd.bmp";
const char BMP_DEFAULT_ENCODED_FILENAME[] = "./encoded_images/suspicious_bitmap.bmp";

BMP _image;

void _bmp_read_from_file(const char *filename, int secret){

    // open it!
    FILE *img_file = fopen(filename, "rb");

    // TODO
    printf("%s\n", filename);

    // bye
    fclose(img_file);
}
