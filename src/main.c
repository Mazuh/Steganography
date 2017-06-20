/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>

#include "ppm.h"
#include "bmp.h"

/* Portable PixMap */
int test_ppm(){

    printf("\n>>> PPM: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
    ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN... Wait for it... DARY! Legendary!!!");

    printf("\n>>> PPM: READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message:\n%s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));

    return 0;
}

/* Bitmap */
int test_bmp(){
    
    BMP *image = _bmp_read_from_file("./default_assets/perfumeadidas31.bmp");
    _bmp_write_with_secret(image, "wadda");

    //printf("\n>>> BMP: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
    //bmp_encode("BMP_DEFAULT_ASSET_FILENAME", "I am not in danger, Skyler. I AM the danger.");

    //printf("\n>>> BMP: READING SECRET INSIDE THE CREATED IMAGE...\n");
    //printf("Discovered message: %s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));

    return 0;
}

int main(){
    //return test_ppm();
    return test_bmp();
}
