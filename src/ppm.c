/**
 * @author Mazuh
 * @brief Portable PixMap (.ppm) image handler
 */

#include <stdio.h>
#include <string.h>

#include "ppm.h"

const unsigned char BIT_SEEK_MASK[8] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
PPM _image;

void ppm_encode(const char *filename, const char *message){
    _ppm_read_from_file(filename);
    _ppm_write_with_secret(message);
}

unsigned char seek_char_bit(unsigned char *sample, int bit_position){
    return (*sample & BIT_SEEK_MASK[bit_position]) == BIT_SEEK_MASK[bit_position];
}

unsigned char color_lsb(unsigned char *color_sample){
    return (*color_sample & 0x1) == 0x1;
}

void set_color_lsb(unsigned char *color_sample, unsigned char bit){
    *color_sample = (bit) ? (*color_sample | 0x1) : (*color_sample & 0xfe);
}

void _ppm_read_from_file(const char *filename){

    // open it!
    FILE *img_file = fopen(filename, "rb");

    // seek file size in bytes
    fseek(img_file, 0, SEEK_END);
    _image.size = ftell(img_file);
    fseek(img_file, 0, SEEK_SET);

    // confirm type
    char type[3];
    fscanf(img_file, " %s ", type);

    // read image dimensions
    fscanf(img_file, " %u %u ", &_image.width, &_image.height);

    // read max color value
    fscanf(img_file, " %hhu ", &_image.max_color);

    // print the whole header
    printf("File: %s\nSize: %lumb, Type: %s, Width: %u, Height: %u\n", filename, _image.size/1048576, type, _image.width, _image.height);

    // now read the image pixels
    Pixel pixel;
    for (int i = 0; i < _image.height; i++){
        for (int j = 0; j < _image.width; j++){
            pixel.red = (unsigned char) fgetc(img_file);
            pixel.green = (unsigned char) fgetc(img_file);
            pixel.blue = (unsigned char) fgetc(img_file);
            _image.pixel_map[i][j] = pixel;
        }
    }

    // bye
    fclose(img_file);
}

void _ppm_write_with_secret(const char *message){
    
    // hello!
    FILE *img_file = fopen(PPM_DEFAULT_ENCODED_FILENAME, "wb");

    // print header
    fputs(PPM_TYPE_BIN, img_file);
    fputs("\n", img_file);
    fprintf(img_file, "%u %u\n", _image.width, _image.height);
    fprintf(img_file, "%hhu\n", _image.max_color);

    // serialize bits
    int message_len = strlen(message);
    unsigned char serialized_message[500];
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

    for (int i = 0; i < _image.height; i++){
        for (int j = 0; j < _image.width; j++){
            
            Pixel pixel = _image.pixel_map[i][j];
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
