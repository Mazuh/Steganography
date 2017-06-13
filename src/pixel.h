/**
 * @author Mazuh
 * @brief Header for pixel handler, common to almost every image handler
 */
#ifndef PIXEL_H
#define PIXEL_H

extern const unsigned char END_OF_SECRET;
extern const unsigned char BIT_SEEK_MASK[8];

/**
 * @brief Each pixel of a ppm image, a color tripled
 */
typedef struct Pixel_struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

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

#endif
