//
// Created by Daniil Kravchenko on 14.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_FILE_OC_H
#define ASSIGNMENT_IMAGE_ROTATION_FILE_OC_H

#include "bmp_io.h"
#include "image.h"
#include <stdio.h>

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum open_status open_file(FILE** file, char* const path, char* const mode);

enum close_status close_file(FILE** file);

enum read_status read_image(FILE** file, char* const path, struct image* const image,
                            enum read_status (*from_format) (FILE* file, struct image* const image));

enum write_status write_image(FILE** file, char* const path, struct image* const image,
                              enum write_status (*to_format) (FILE* file, struct image* const image ));

#endif //ASSIGNMENT_IMAGE_ROTATION_FILE_OC_H
