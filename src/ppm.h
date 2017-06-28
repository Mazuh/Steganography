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
    unsigned char *found_lsb; /* all less significant bits collected from pixels */
    unsigned int found_lsb_len;
    Pixel **pixel_map; /* image content */
} PPM;

/**
 * @brief Gets a ppm image file and writes a message in it.
 */
void ppm_encode(const char *filename, const char *message, const char *resulting_filename);

/**
 * @brief Gets a ppm image file with a secret and discover its message.
 */
char *ppm_decode(const char *filename);

/**
 * @brief (Private) Reads the original image file.
 */
PPM *_ppm_read_from_file(const char *filename);

/**
 * @brief (Private) Persists the image and also writes a secret message.
 */
void _ppm_write_with_secret(PPM *image, const char *message, const char *resulting_filename);

#endif
