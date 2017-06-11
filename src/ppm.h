/**
 * @author Mazuh
 * @brief Header for Portable PixMap (.ppm) image handler
 * @see http://netpbm.sourceforge.net/doc/ppm.html
 */
#ifndef PPM_H
#define PPM_H

#define PPM_DEFAULT_ENCODED_FILENAME "./encoded_images/suspicious_portable_pixmap.ppm"
#define PPM_TYPE_ASCII "P3"
#define PPM_TYPE_BIN "P6"

/**
 * @brief Each pixel of a ppm image
 */
typedef struct Pixel_struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

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
 * @brief Gets the less significant bit of a color sample.
 */
unsigned char color_lsb(unsigned char *color_sample);

/**
 * @brief Changes the less significant bit of a color sample.
 */
void set_color_lsb(unsigned char *color_sample, unsigned char bit);

/**
 * @brief (Private) Reads the original image file.
 */
void _ppm_read_from_file(const char *filename);

/**
 * @brief (Private) Persists the image and also writes a secret message.
 */
void _ppm_write_with_secret(const char *message);

#endif
