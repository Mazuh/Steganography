/**
 * @author Mazuh
 * @brief Header for Portable PixMap (.ppm) image handler
 * @see http://netpbm.sourceforge.net/doc/ppm.html
 */
#ifndef PPM_H
#define PPM_H

#define PPM_TYPE_ASCII "P3"
#define PPM_TYPE_BIN "P6"

/**
 * @brief Each pixel of a ppm image
 */
typedef struct Pixel_struct{
    unsigned char RED;
    unsigned char GREEN;
    unsigned char BLUE;
} Pixel;

/**
 * @brief A ppm image file
 */
typedef struct PPM_struct{
	FILE *file; /* whole image file representation */
    unsigned long size; /* in bytes */
    unsigned int width; /* pixel amounts per line of content */
    unsigned int height; /* pixel amounts per column */
    unsigned char max_color; /* max color value */
    unsigned char max_significant_bits; /* maximum amount of free significant bits */
    Pixel pixel_map[4294967295]; /* image content */
} PPM;

/**
 * @brief Reads an image pointed to by filename
 */
PPM *ppm_read(const char *filename);

#endif
