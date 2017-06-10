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
 * @brief Reads an image pointed to by filename
 */
PPM *ppm_read(const char *filename);

#endif
