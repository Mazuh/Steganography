/**
 * @author Mazuh
 * @brief Header for Portable PixMap (.ppm) image handler
 * @see http://netpbm.sourceforge.net/doc/ppm.html
 */
#ifndef PPM_H
#define PPM_H

#include "pixel.h"

extern const char PPM_DEFAULT_ASSET_FILENAME[];
extern const char PPM_DEFAULT_ENCODED_FILENAME[];

#define PPM_TYPE_ASCII "P3"
#define PPM_TYPE_BIN "P6"

/**
 * @brief A ppm image file
 */
typedef struct PPM_struct{
    unsigned long size; /* in bytes */
    unsigned int width; /* pixel amounts per line of content */
    unsigned int height; /* pixel amounts per column */
    unsigned char max_color; /* max color value */
    Pixel pixel_map[10000][10000]; /* image content */
} PPM;

/**
 * @brief Gets a ppm image file and writes a message in it.
 */
void ppm_encode(const char *filename, const char *message);

/**
 * @brief Gets a ppm image file with a secret and discover its message.
 */
char *ppm_decode(const char *filename);

/**
 * @brief (Private) Reads the original image file.
 */
void _ppm_read_from_file(const char *filename, int secret);

/**
 * @brief (Private) Persists the image and also writes a secret message.
 */
void _ppm_write_with_secret(const char *message);

#endif
