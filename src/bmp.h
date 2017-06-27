/**
 * @author Mazuh
 * @brief Header for Bitmap (.bmp) image handler
 * @see http://www.digicamsoft.com/bmp/bmp.html
 */
#ifndef BMP_H
#define BMP_H

#include "pixel.h"

extern const char BMP_DEFAULT_ASSET_FILENAME[];
extern const char BMP_DEFAULT_ENCODED_FILENAME[];


/**
 * @brief A bmp file header
 */
 typedef struct FileHeaderBMP_struct{
    char type[3];
    unsigned int file_size;
    unsigned int reserved;
    unsigned int offset;
} FileHeaderBMP;

/**
 * @brief A bmp image header
 */
 typedef struct ImageHeaderBMP_struct{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes_qtt;
    unsigned short bits_per_pixel;
    unsigned int compression_type;
    unsigned int image_size;
    unsigned int horizontal_resolution;
    unsigned int vertical_resolution;
    unsigned int colors_qtt;
    unsigned int important_colors_qtt;
} ImageHeaderBMP;

/**
 * @brief A bmp image and its headers
 */
typedef struct BMP_struct{
    FileHeaderBMP *file_header;
    ImageHeaderBMP *image_header;
    Pixel **pixel_map;
    unsigned char *found_lsb; /* all least significant bits collected from pixels */
    unsigned long found_lsb_len;
} BMP;


/**
 * @brief Gets a bmp image file and writes a message in it.
 */
void bmp_encode(const char *filename, const char *message);

/**
 * @brief Gets a bmp image file with a secret and discover its message.
 */
char *bmp_decode(const char *filename);

/**
 * @brief (Private) Reads the original image file.
 */
BMP *_bmp_read_from_file(const char *filename);

/**
 * @brief (Private) Persists the image and also writes a secret message.
 */
void _bmp_write_with_secret(BMP *image, const char *message);

#endif
