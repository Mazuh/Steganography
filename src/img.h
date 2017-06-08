/**
 * @author Mazuh
 * @brief Header for bitmap (.bmp) image handler
 */
#ifndef IMG_H
#define IMG_H

/**
 * @brief An image file
 */
typedef struct ImageFile_struct{
	FILE file;
    unsigned long size;
} ImageFile;

/**
 * @brief How many byte offs a bmp image has
 */
void count_bytes_off(ImageFile *image);

#endif
