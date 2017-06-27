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
    ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN...\nWait for it...\nDARY!\nLegendary!!!");

    printf("\n>>> PPM: READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message:\n\n%s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));

    return 0;
}

/* Bitmap */
int test_bmp(){
    
    printf("\n>>> BMP: TRYING TO CREATE AN IMAGE WITH SECRET...\n");   
    bmp_encode(BMP_DEFAULT_ASSET_FILENAME, "You clearly don't know who you're talking to, so let me clue you in.\nI am not in danger, Skyler. I AM THE DANGER.\nA guy opens his door and gets shot and you think that of me?\nNo.\nI am... the one who knocks!");

    printf("\n>>> BMP: READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message:\n\n%s\n", bmp_decode(BMP_DEFAULT_ENCODED_FILENAME));

    return 0;
}

int main(){
    //return test_ppm();
    return test_bmp();
}
