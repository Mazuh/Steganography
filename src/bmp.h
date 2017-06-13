/**
 * @author Mazuh
 * @brief Header for Portable PixMap (.ppm) image handler
 * @see http://netpbm.sourceforge.net/doc/ppm.html
 */

#ifndef BMP_H
#define BMP_H

#define BMP_DEFAULT_ENCODED_FILENAME "./encoded_images/suspicious_bitmap.bmp"
#define BMP_DEFAULT_ASSET_FILENAME "./default_assets/imd.bmp"

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
 * @brief Gets a ppm image file with a secret and discover its message.
 */
char *ppm_decode(const char *filename);

/**
 * @brief Gets the bit of a character sample, based on its position (from left to right, 0~7).
 */
unsigned char seek_char_bit(unsigned char *sample, int bit_position);

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
void _ppm_read_from_file(const char *filename, int secret);

/**
 * @brief (Private) Persists the image and also writes a secret message.
 */
void _ppm_write_with_secret(const char *message);

#endif
