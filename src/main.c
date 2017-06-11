/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>

#include "ppm.h"

int main(){
    ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN... Wait for it... DARY! Legendary!!!");
    //printf("Discovered message: %s\n", ppm.decode(PPM_DEFAULT_ENCODED_FILENAME));
    return 0;
}
