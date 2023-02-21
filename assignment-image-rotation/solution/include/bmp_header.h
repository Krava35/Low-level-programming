//
// Created by Daniil Kravchenko on 14.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_HEADER_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_HEADER_H

#include "image.h"
#include  <stdint.h>
struct __attribute__((packed)) bmp_header{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct bmp_header create_header(struct image* const image);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_HEADER_H
