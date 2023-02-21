//
// Created by Daniil Kravchenko on 14.01.2022.
//

#include "../include/file_io.h"
#include <stdio.h>

enum open_status open_file(FILE** file, char* const path, char* const mode){
    *file = fopen(path, mode);
    if(!*file){
        return OPEN_ERROR;
    }
    return  OPEN_OK;
}

enum close_status close_file(FILE** file){
    if (fclose(*file)){
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}

enum read_status read_image(FILE** file, char* const path, struct image* const image,
                            enum read_status (*from_format) (FILE* file, struct image* const image)){
    enum open_status status = open_file(file, path, "rb");
    switch (status) {
        case OPEN_OK:
            fprintf(stdout, "The file '%s' is opened successfully!", path);
            break;
        case OPEN_ERROR:
            fprintf(stderr, "Error, the file '%s' isn't opened.", path);
            break;
    }
    return from_format(*file, image);
}

enum write_status write_image(FILE** file, char* const path, struct image* const image,
                              enum write_status (*to_format) (FILE* file, struct image* const image )){
    enum open_status status = open_file(file, path, "wb");
    switch (status) {
        case OPEN_OK:
            fprintf(stdout, "The file '%s' is opened successfully!", path);
            break;
        case OPEN_ERROR:
            fprintf(stderr, "Error, the file '%s' isn't opened.", path);
            break;
    }
    return to_format(*file, image);
}
