/**
 * @author Mazuh
 * @brief Main function for Steganography project
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"
#include "bmp.h"

/* Portable PixMap 
int test_ppm(){

    printf("\n>>> PPM: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
    ppm_encode(PPM_DEFAULT_ASSET_FILENAME, "This project is LEGEN...\nWait for it...\nDARY!\nLegendary!!!");

    printf("\n>>> PPM: READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message:\n\n%s\n", ppm_decode(PPM_DEFAULT_ENCODED_FILENAME));

    return 0;
}
*/
/* Bitmap 
int test_bmp(){
    
    printf("\n>>> BMP: TRYING TO CREATE AN IMAGE WITH SECRET...\n");   
    bmp_encode(BMP_DEFAULT_ASSET_FILENAME, "You clearly don't know who you're talking to, so let me clue you in.\nI am not in danger, Skyler. I AM THE DANGER.\nA guy opens his door and gets shot and you think that of me?\nNo.\nI am... the one who knocks!");

    printf("\n>>> BMP: READING SECRET INSIDE THE CREATED IMAGE...\n");
    printf("Discovered message:\n\n%s\n", bmp_decode(BMP_DEFAULT_ENCODED_FILENAME));

    return 0;
}
*/
/* Dumb file reading */
char *_dcontent_from_file(char *filename){

    FILE *file = fopen(filename, "rb");
    
    if (file != NULL){
        
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        char *content = malloc(size+1);

        for (int i = 0; i < size; i++){
            content[i] = fgetc(file);
        }
        content[size] = '\0';
        fclose(file);
        return content;

    } else{
        printf("Unable to open: %s.\n", filename);
        return "";
    }
}

/* Dumb file writing */
int _dcontent_to_file(char *filename, char *content){

    FILE *file = fopen(filename, "wb");
    long content_len = strlen(content);

    if (file != NULL){

        for (int i = 0; i < content_len; i++){
            fputc(content[i], file);
        }

        fclose(file);
        return 1;

    } else{
        printf("Unable to write: %s.\n", filename);
        return 0;
    }
}

int main(int args_len, char *args[]){

    if (args_len == 5 && args[1][1] == 'e'){ // ENCONDING!

        char *host_filename = args[2];
        char *secret_filename = args[3];
        char *resulting_filename = args[4];

        int host_filename_len = strlen(host_filename);

        if (host_filename[host_filename_len-1] == 'm' && host_filename[host_filename_len-2] == 'p' && host_filename[host_filename_len-3] == 'p'){
            printf("\n>>> PPM: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
            ppm_encode(host_filename, _dcontent_from_file(secret_filename), resulting_filename);

        } else if (host_filename[host_filename_len-1] == 'p' && host_filename[host_filename_len-2] == 'm' && host_filename[host_filename_len-3] == 'b'){
            printf("\n>>> BMP: TRYING TO CREATE AN IMAGE WITH SECRET...\n");
            bmp_encode(host_filename, _dcontent_from_file(secret_filename), resulting_filename);

        } else {
            printf("Unsupported file type: should be .ppm or .bmp.\n");
            return 1;
        }

        return 0;

    } else if(args_len == 4 && args[1][1] == 'd'){ // DECODING!

        char *host_filename = args[2];
        char *secret_filename = args[3];

        int host_filename_len = strlen(host_filename);

        if (host_filename[host_filename_len-1] == 'm' && host_filename[host_filename_len-2] == 'p' && host_filename[host_filename_len-3] == 'p'){
            
            printf("\n>>> PPM: READING SECRET INSIDE THE CREATED IMAGE...\n");

            char *message = ppm_decode(host_filename);

            if (strlen(message)){
                if (_dcontent_to_file(secret_filename, message)){
                    printf("Discovered message file: %s\n", secret_filename);
                } else{
                    printf("Failed to write at %s file. Here's the message then:\n\n%s\n", secret_filename, message);
                }
            } else{
                printf("No message could be found.\n");
                return 1;
            }

        } else if (host_filename[host_filename_len-1] == 'p' && host_filename[host_filename_len-2] == 'm' && host_filename[host_filename_len-3] == 'b'){
            printf("\n>>> BMP: READING SECRET INSIDE THE CREATED IMAGE...\n");

            char *message = bmp_decode(host_filename);

            if (strlen(message)){
                if (_dcontent_to_file(secret_filename, message)){
                    printf("Discovered message file: %s\n", secret_filename);
                } else{
                    printf("Failed to write at %s file. Here's the message then:\n\n%s\n", secret_filename, message);
                }
            } else{
                printf("No message could be found.\n");
                return 1;
            }

        } else {
            printf("Unsupported file type: should be .ppm or .bmp.\n");
            return 1;
        }

        return 0;

    } else{
        printf("Invalid flag. Check the readme.md file in the repository for cool instructions.\n");
        return 1;
    }

    return 0;
}
