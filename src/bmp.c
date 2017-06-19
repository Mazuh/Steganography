/**
 * @author Mazuh
 * @brief Bitmap (.bmp) image handler
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bmp.h"

const char BMP_DEFAULT_ASSET_FILENAME[] = "./default_assets/imd.bmp";
const char BMP_DEFAULT_ENCODED_FILENAME[] = "./encoded_images/suspicious_bitmap.bmp";

#define SIZE_INT 4
#define SIZE_SHORT 2

void _bmp_read_from_file(const char *filename, int secret){

    // open it!
    FILE *img_file = fopen(filename, "rb");
    printf("File: %s\n", filename);

    // scanning file header
    FileHeaderBMP *fheader = malloc(sizeof(FileHeaderBMP));
    fheader->type[0] = fgetc(img_file);
    fheader->type[1] = fgetc(img_file);
    fheader->type[2] = '\0';
    fread(&fheader->file_size, SIZE_INT, 1, img_file);
    fread(&fheader->reserved,  SIZE_INT, 1, img_file);
    fread(&fheader->offset,    SIZE_INT, 1, img_file);

    printf("Type: %s, Size: %u, Reserved: %u, Offset: %u\n", fheader->type, fheader->file_size, fheader->reserved, fheader->offset);

    // scanning image header
    ImageHeaderBMP *iheader = malloc(sizeof(ImageHeaderBMP));
    fread(&iheader->header_size,           SIZE_INT,   1, img_file);
    fread(&iheader->width,                 SIZE_INT,   1, img_file);
    fread(&iheader->height,                SIZE_INT,   1, img_file);
    fread(&iheader->planes_qtt,            SIZE_SHORT, 1, img_file);
    fread(&iheader->bits_per_pixel,        SIZE_SHORT, 1, img_file);
    fread(&iheader->compression_type,      SIZE_INT,   1, img_file);
    fread(&iheader->image_size,            SIZE_INT,   1, img_file);
    fread(&iheader->horizontal_resolution, SIZE_INT,   1, img_file);
    fread(&iheader->vertical_resolution,   SIZE_INT,   1, img_file);
    fread(&iheader->colors_qtt,            SIZE_INT,   1, img_file);
    fread(&iheader->important_colors_qtt,  SIZE_INT,   1, img_file);

    printf("Header size: %u, Width: %d, Height: %d\n", iheader->header_size, iheader->width, iheader->height);
    printf("Color planes: %hu, Bits per pixel: %hu, Compression: %u\n", iheader->planes_qtt, iheader->bits_per_pixel, iheader->compression_type);
    printf("Image size: %u, Horizontal resolution: %d, Vertical resolution: %d\n", iheader->image_size, iheader->horizontal_resolution, iheader->vertical_resolution);
    printf("Colors: %u, Important colors: %u\n", iheader->colors_qtt, iheader->important_colors_qtt);

    // ...

    // bye
    fclose(img_file);
}
