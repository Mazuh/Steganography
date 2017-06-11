/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>

#include "ppm.h"

int main(){
    ppm_encode("./default_assets/imd.ppm", "This project is LEGEN...\nWait for it...\nDARY! Legendary!!!");
    unsigned char color = 129;
    printf("%hhu\n", color);
    set_color_lsb(&color, 0);
    printf("%hhu\n", color);
    return 0;
}
