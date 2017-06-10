/**
 * @author Mazuh
 * @brief Portable PixMap (.ppm) image handler
 */

#include <stdio.h>
#include "ppm.h"

PPM _image;

void ppm_encode(const char *filename, const char *message){
    _ppm_read_from_file(filename);
    _ppm_write_with_secret(message);
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

    // print image content
    Pixel pixel;
    for (int i = 0; i < _image.height; i++){
        for (int j = 0; j < _image.width; j++){
            pixel = _image.pixel_map[i][j];
            fputc(pixel.red, img_file);
            fputc(pixel.green, img_file);
            fputc(pixel.blue, img_file);
        }
    }

    // bye :c
    fclose(img_file);

    printf("Output file: ");
    printf(PPM_DEFAULT_ENCODED_FILENAME);
    printf("\n");

}
