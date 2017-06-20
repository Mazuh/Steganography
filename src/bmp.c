/**
 * @author Mazuh
 * @brief Bitmap (.bmp) image handler
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bmp.h"

const char BMP_DEFAULT_ASSET_FILENAME[] = "./default_assets/imd.bmp";
const char BMP_DEFAULT_ENCODED_FILENAME[] = "./encoded_images/suspicious_bitmap.bmp";

#define SIZE_INT 4
#define SIZE_SHORT 2

BMP* _bmp_read_from_file(const char *filename){

    // open it!
    BMP *image = malloc(sizeof(BMP));
    FILE *img_file = fopen(filename, "rb");

    printf("File: %s\n", filename);

    // scanning file header
    FileHeaderBMP *fheader = malloc(sizeof(FileHeaderBMP));
    
    fheader->type[0] = fgetc(img_file);
    fheader->type[1] = fgetc(img_file);
    fheader->type[2] = '\0';
    fread(&fheader->file_size, SIZE_INT, 1, img_file);
    fread(&fheader->reserved,  SIZE_INT, 1, img_file);
    fread(&fheader->offset,    SIZE_INT, 1, img_file);

    printf("Type: %s, Size: %u, Reserved: %u, Offset: %u\n", fheader->type, fheader->file_size, fheader->reserved, fheader->offset);

    image->file_header = fheader;

    // scanning image header
    ImageHeaderBMP *iheader = malloc(sizeof(ImageHeaderBMP));
    
    fread(&iheader->header_size,           SIZE_INT,   1, img_file);
    fread(&iheader->width,                 SIZE_INT,   1, img_file);
    fread(&iheader->height,                SIZE_INT,   1, img_file);
    fread(&iheader->planes_qtt,            SIZE_SHORT, 1, img_file);
    fread(&iheader->bits_per_pixel,        SIZE_SHORT, 1, img_file);
    fread(&iheader->compression_type,      SIZE_INT,   1, img_file);
    fread(&iheader->image_size,            SIZE_INT,   1, img_file);
    fread(&iheader->horizontal_resolution, SIZE_INT,   1, img_file);
    fread(&iheader->vertical_resolution,   SIZE_INT,   1, img_file);
    fread(&iheader->colors_qtt,            SIZE_INT,   1, img_file);
    fread(&iheader->important_colors_qtt,  SIZE_INT,   1, img_file);

    printf("Header size: %u, Width: %d, Height: %d\n", iheader->header_size, iheader->width, iheader->height);
    printf("Color planes: %hu, Bits per pixel: %hu, Compression: %u\n", iheader->planes_qtt, iheader->bits_per_pixel, iheader->compression_type);
    printf("Image size: %u, Horizontal resolution: %d, Vertical resolution: %d\n", iheader->image_size, iheader->horizontal_resolution, iheader->vertical_resolution);
    printf("Colors: %u, Important colors: %u\n", iheader->colors_qtt, iheader->important_colors_qtt);

    image->image_header = iheader;
    
    // scanning image pixels
    Pixel pixel;
    image->pixel_map = malloc(iheader->height * sizeof(Pixel*));
    //image->found_lsb = malloc(0);
    //image->found_lsb_len = 0;

    for (int i = 0; i < iheader->height; i++){
        image->pixel_map[i] = (Pixel*) malloc(iheader->width*sizeof(Pixel));

        for (int j = 0; j < iheader->width; j++){

            pixel.red = (unsigned char) fgetc(img_file);
            pixel.green = (unsigned char) fgetc(img_file);
            pixel.blue = (unsigned char) fgetc(img_file);
            image->pixel_map[i][j] = pixel;

            //image->found_lsb = realloc(image->found_lsb, image->found_lsb_len+3);
            //image->found_lsb[image->found_lsb_len++] = color_lsb(&pixel.red);
            //image->found_lsb[image->found_lsb_len++] = color_lsb(&pixel.green);
            //image->found_lsb[image->found_lsb_len++] = color_lsb(&pixel.blue);

        }
    }

    // bye
    fclose(img_file);
    return image;
}

void _bmp_write_with_secret(BMP *image, const char *message){
    // hello!
    FILE *img_file = fopen(BMP_DEFAULT_ENCODED_FILENAME, "wb");

    // write file header
    FileHeaderBMP *fheader = image->file_header;
    
    fputc(fheader->type[0], img_file);
    fputc(fheader->type[1], img_file);
    fwrite(&fheader->file_size, SIZE_INT, 1, img_file);
    fwrite(&fheader->reserved,  SIZE_INT, 1, img_file);
    fwrite(&fheader->offset,    SIZE_INT, 1, img_file);

    // write image hader
    ImageHeaderBMP *iheader = image->image_header;

    fwrite(&iheader->header_size,           SIZE_INT,   1, img_file);
    fwrite(&iheader->width,                 SIZE_INT,   1, img_file);
    fwrite(&iheader->height,                SIZE_INT,   1, img_file);
    fwrite(&iheader->planes_qtt,            SIZE_SHORT, 1, img_file);
    fwrite(&iheader->bits_per_pixel,        SIZE_SHORT, 1, img_file);
    fwrite(&iheader->compression_type,      SIZE_INT,   1, img_file);
    fwrite(&iheader->image_size,            SIZE_INT,   1, img_file);
    fwrite(&iheader->horizontal_resolution, SIZE_INT,   1, img_file);
    fwrite(&iheader->vertical_resolution,   SIZE_INT,   1, img_file);
    fwrite(&iheader->colors_qtt,            SIZE_INT,   1, img_file);
    fwrite(&iheader->important_colors_qtt,  SIZE_INT,   1, img_file);

/*
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
*/
    // print image content, with hidden message
    //int hidden_bits = 0;

    for (int i = 0; i < iheader->height; i++){
        for (int j = 0; j < iheader->width; j++){
            
            Pixel pixel = image->pixel_map[i][j];
            unsigned char pixel_colors[3] = {pixel.red, pixel.green, pixel.blue};

            for (int k = 0; k < 3; k++){
                /*if (hidden_bits < serialized_message_len)
                    set_color_lsb(&pixel_colors[k], serialized_message[hidden_bits]);
                else
                    set_color_lsb(&pixel_colors[k], 0);*/
                fputc(pixel_colors[k], img_file);
                //hidden_bits++;
            }
        }
    }

    // bye :c
    fclose(img_file);

    printf("Output file: ");
    printf(BMP_DEFAULT_ENCODED_FILENAME);
    printf("\n");

}
