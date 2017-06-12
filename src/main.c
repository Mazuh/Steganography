/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>

#include "ppm.h"

int main(){
    
    printf("\n>>> TRYING TO CREATE AN IMAGE WITH SECRET...\n");
    ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN... Wait for it... DARY! Legendary!!!");
    
    printf("\n>>> READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message: %s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));
    
    return 0;
}
