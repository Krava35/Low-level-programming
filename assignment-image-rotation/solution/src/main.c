
#include "../include/file_io.h"
#include "../include/image_rotation.h"
#include <stdio.h>

int main( int argc, char** argv ) {
    if (argc != 3){
        fprintf(stderr, "Incorrect number of arguments.");
        return 1;
    }
    FILE* input_file = NULL;
    FILE* output_file = NULL;
    struct image image;
    enum read_status read_status = read_image(&input_file, argv[1], &image, from_bmp);
    if (read_status){
        switch (read_status) {
            case READ_INVALID_SIGNATURE:
                fprintf(stderr, "Incorrect file signature.");
                break;
            case READ_INVALID_HEADER:
                fprintf(stderr, "Incorrect file header.");
                break;
            case READ_INVALID_BITS:
                fprintf(stderr, "Incorrect size.");
                break;
            case READ_ERROR:
                fprintf(stderr, "Read error.");
                break;
            case READ_OK:
                break;
        }
        return 1;
    }
    enum close_status close_status = close_file(&input_file);
    if (close_status){
        fprintf(stderr, "File close error.");
        destroy_image(&image);
        return 1;
    }
    struct image rotated_image = rotate(&image);
    enum write_status write_status = write_image(&output_file, argv[2], &rotated_image, to_bmp);
    if (write_status){
        fprintf(stderr, "File write error.");
        destroy_image(&image);
        destroy_image(&rotated_image);
        return 1;
    }
    close_status = close_file(&output_file);
    if(close_status){
        fprintf(stderr, "File close error.");
        destroy_image(&image);
        destroy_image(&rotated_image);
        return 1;
    }
    destroy_image(&image);
    destroy_image(&rotated_image);
    return 0;
}
