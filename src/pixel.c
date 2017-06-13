/**
 * @author Mazuh
 * @brief Pixel handler, common to almost every image handler
 */

#include "pixel.h"

const unsigned char END_OF_SECRET = 0x1b;
const unsigned char BIT_SEEK_MASK[8] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};

unsigned char seek_char_bit(unsigned char *sample, int bit_position){
    return (*sample & BIT_SEEK_MASK[bit_position]) == BIT_SEEK_MASK[bit_position];
}

unsigned char color_lsb(unsigned char *color_sample){
    return (*color_sample & 0x1) == 0x1;
}

void set_color_lsb(unsigned char *color_sample, unsigned char bit){
    *color_sample = (bit) ? (*color_sample | 0x1) : (*color_sample & 0xfe);
}
