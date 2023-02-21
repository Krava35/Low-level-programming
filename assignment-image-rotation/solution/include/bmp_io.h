//
// Created by Daniil Kravchenko on 14.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_IO_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_IO_H

#include "bmp_header.h"
#include <stdio.h>

/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_ERROR
    /* коды других ошибок  */
};

enum read_status from_bmp( FILE* file, struct image* const image);

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

enum write_status to_bmp( FILE* file, struct image* const image );

enum read_status check_bmp(const struct bmp_header header);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_IO_H
