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
 * @brief A bmp image file
 */
typedef struct BMP_struct{
    unsigned long size;
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
void _bmp_read_from_file(const char *filename, int secret);

/**
 * @brief (Private) Persists the image and also writes a secret message.
 */
void _bmp_write_with_secret(const char *message);

#endif
