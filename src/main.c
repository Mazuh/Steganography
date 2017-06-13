/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>

#include "ppm.h"

/* Portable PixMap */
int test_ppm(){
    
    printf("\n>>> PPM: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
    ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN... Wait for it... DARY! Legendary!!!");
    
    printf("\n>>> PPM: READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message: %s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));

    return 0;
}

/* Bitmap */
int test_bmp(){
    
    printf("\n>>> BMP: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
    //ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN... Wait for it... DARY! Legendary!!!");
    
    //printf("\n>>> BMP: READING SECRET INSIDE THE CREATED IMAGE...\n");
    //printf("Discovered message: %s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));

    return 0;
}

int main(){
    return test_bmp();
}
