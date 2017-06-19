/**
 * @author Mazuh
 * @brief Portable PixMap (.ppm) image handler
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ppm.h"

const char PPM_DEFAULT_ASSET_FILENAME[] = "./default_assets/imd.ppm";
const char PPM_DEFAULT_ENCODED_FILENAME[] = "./encoded_images/suspicious_portable_pixmap.ppm";

void ppm_encode(const char *filename, const char *message){
    PPM *image = _ppm_read_from_file(filename, 0);
    _ppm_write_with_secret(image, message);
}

char *ppm_decode(const char *filename){
    PPM *image = _ppm_read_from_file(filename, 1);

    int message_len = 0;
    unsigned char found_char;

    char *message = malloc(1);

    for (int i = 0; i < 500; i += 8){
        found_char = (
            image->found_lsb[i] << 7
            | image->found_lsb[i+1] << 6
            | image->found_lsb[i+2] << 5
            | image->found_lsb[i+3] << 4
            | image->found_lsb[i+4] << 3
            | image->found_lsb[i+5] << 2
            | image->found_lsb[i+6] << 1
            | image->found_lsb[i+7]
        );

        if (found_char == END_OF_SECRET){
            message[message_len++] = '\0';
            break;
        } else{
            message[message_len++] = (char) found_char;
            message = realloc(message, message_len+1);
        }

    }

    return message;
}

PPM* _ppm_read_from_file(const char *filename, int secret){

    // open it!
    PPM *image = malloc(sizeof(PPM));
    FILE *img_file = fopen(filename, "rb");

    // seek file size in bytes
    fseek(img_file, 0, SEEK_END);
    image->size = ftell(img_file);
    fseek(img_file, 0, SEEK_SET);

    // scanning header
    char type[3];
    fscanf(img_file, " %s ", type);
    fscanf(img_file, " %u %u ", &image->width, &image->height);
    fscanf(img_file, " %hhu ", &image->max_color);

    printf("File: %s\nSize: %lumb, Type: %s, Width: %u, Height: %u\n", filename, image->size/1048576, type, image->width, image->height);

    // preparing memory to read pixels
    image->pixel_map = malloc(image->height*sizeof(Pixel*));

    for(int i=0; i<image->height; i++)
        (image->pixel_map)[i] = (Pixel*) malloc(image->width*sizeof(Pixel));

    // scanning image pixels
    Pixel pixel;
    unsigned int found_lsb_len = 0;

    image->found_lsb = malloc(0);

    for (int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j++){
            pixel.red = (unsigned char) fgetc(img_file);
            pixel.green = (unsigned char) fgetc(img_file);
            pixel.blue = (unsigned char) fgetc(img_file);
            image->pixel_map[i][j] = pixel;
            if (found_lsb_len < 498 && secret){
                image->found_lsb = realloc(image->found_lsb, found_lsb_len+3);
                image->found_lsb[found_lsb_len++] = color_lsb(&pixel.red);
                image->found_lsb[found_lsb_len++] = color_lsb(&pixel.green);
                image->found_lsb[found_lsb_len++] = color_lsb(&pixel.blue);
            }
        }
    }

    image->found_lsb_len = (unsigned int) found_lsb_len;

    // bye
    fclose(img_file);
    return image;
}

void _ppm_write_with_secret(PPM *image, const char *message){

    // hello!
    FILE *img_file = fopen(PPM_DEFAULT_ENCODED_FILENAME, "wb");

    // print header
    fputs(PPM_TYPE_BIN, img_file);
    fputs("\n", img_file);
    fprintf(img_file, "%u %u\n", image->width, image->height);
    fprintf(img_file, "%hhu\n", image->max_color);

    // serialize bits
    int message_len = strlen(message);
    unsigned char *serialized_message = malloc(strlen(message)*8 + 8);
    int hidden_bytes = 0;
    int serialized_message_len = message_len * 8;

    for (int i = 0; i < serialized_message_len; i += 8){
        for (int j = 0; j < 8; j++){
            serialized_message[i+j] = seek_char_bit((unsigned char *) &message[hidden_bytes], j);
        }
        hidden_bytes++;
    }

    // serialize ESC character, saying that the message has ended
    serialized_message[serialized_message_len++] = (unsigned char) 0;
    serialized_message[serialized_message_len++] = (unsigned char) 0;
    serialized_message[serialized_message_len++] = (unsigned char) 0;
    serialized_message[serialized_message_len++] = (unsigned char) 1;
    serialized_message[serialized_message_len++] = (unsigned char) 1;
    serialized_message[serialized_message_len++] = (unsigned char) 0;
    serialized_message[serialized_message_len++] = (unsigned char) 1;
    serialized_message[serialized_message_len++] = (unsigned char) 1;

    // print image content, with hidden message
    int hidden_bits = 0;

    for (int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j++){
            
            Pixel pixel = image->pixel_map[i][j];
            unsigned char pixel_colors[3] = {pixel.red, pixel.green, pixel.blue};

            for (int k = 0; k < 3; k++){
                if (hidden_bits < serialized_message_len)
                    set_color_lsb(&pixel_colors[k], serialized_message[hidden_bits]);
                else
                    set_color_lsb(&pixel_colors[k], 0);
                fputc(pixel_colors[k], img_file);
                hidden_bits++;
            }

        }
    }

    // bye :c
    fclose(img_file);

    printf("Output file: ");
    printf(PPM_DEFAULT_ENCODED_FILENAME);
    printf("\n");

}
