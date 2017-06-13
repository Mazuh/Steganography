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
    printf("File: %s\n", filename);

    // scanning file header
    //unsigned short type = 19778;
    char type[3];
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;
    
    type[0] = fgetc(img_file);
    type[1] = fgetc(img_file);
    type[2] = '\0';
    fread(&size, 4, 1, img_file);
    fread(&reserved, 4, 1, img_file);
    fread(&offset, 4, 1, img_file);

    printf("Type: %s, Size: %u, Reserved: %u, Offset: %u\n", type, size, reserved, offset);

    // bye
    fclose(img_file);
}
