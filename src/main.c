/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>

#include "ppm.h"

int main(){
    ppm_encode("./default_assets/imd.ppm", "This project is LEGEN... Wait for it... DARY! Legendary!!!");
    return 0;
}
