/**
 * @author Mazuh
 * @brief Bitmap (.bmp) image handler
 */

#include <stdio.h>
#include <string.h>

#include "bmp.h"

const char BMP_DEFAULT_ASSET_FILENAME[] = "./default_assets/imd.bmp";
const char BMP_DEFAULT_ENCODED_FILENAME[] = "./encoded_images/suspicious_bitmap.bmp";

#define SIZE_INT 4
#define SIZE_SHORT 2

BMP _image;

void _bmp_read_from_file(const char *filename, int secret){

    // open it!
    FILE *img_file = fopen(filename, "rb");
    printf("File: %s\n", filename);

    // scanning file header
    char type[3];
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;

    type[0] = fgetc(img_file);
    type[1] = fgetc(img_file);
    type[2] = '\0';
    fread(&size, SIZE_INT, 1, img_file);
    fread(&reserved, SIZE_INT, 1, img_file);
    fread(&offset, SIZE_INT, 1, img_file);

    printf("Type: %s, Size: %u, Reserved: %u, Offset: %u\n", type, size, reserved, offset);

    // scanning image header
    unsigned int header_size;
    int width;
    int height;

    unsigned short planes_qtt;
    unsigned short bits_per_pixel;
    unsigned int compression_type;

    unsigned int image_size;
    int horizontal_resolution;
    int vertical_resolution;

    unsigned int colors_qtt;
    unsigned int important_colors_qtt;

	fread(&header_size, SIZE_INT, 1, img_file);
	fread(&width, SIZE_INT, 1, img_file);
	fread(&height, SIZE_INT, 1, img_file);

	fread(&planes_qtt, SIZE_SHORT, 1, img_file);
	fread(&bits_per_pixel, SIZE_SHORT, 1, img_file);
	fread(&compression_type, SIZE_INT, 1, img_file);
	
    fread(&image_size, SIZE_INT, 1, img_file);
	fread(&horizontal_resolution, SIZE_INT, 1, img_file);
	fread(&vertical_resolution, SIZE_INT, 1, img_file);

	fread(&colors_qtt, SIZE_INT, 1, img_file);
	fread(&important_colors_qtt, SIZE_INT, 1, img_file);

    printf("Header size: %u, Width: %d, Height: %d\n", header_size, width, height);
    printf("Color planes: %hu, Bits per pixel: %hu, Compression: %u\n", planes_qtt, bits_per_pixel, compression_type);
    printf("Image size: %u, Horizontal resolution: %d, Vertical resolution: %d\n", image_size, horizontal_resolution, vertical_resolution);
    printf("Colors: %u, Important colors: %u\n", colors_qtt, important_colors_qtt);

    // scanning colors
    // TODO

    // bye
    fclose(img_file);
}
