//
// Created by Daniil Kravchenko on 14.01.2022.
//

#include "../include/bmp_header.h"
#include "../include/bmp_io.h"

static const uint16_t BF_TYPE = 0x4D42;
static const uint32_t BI_SIZE = 40;
static const uint16_t BIT_COUNT = 24;

struct bmp_header create_header(struct image* const image){
    struct bmp_header header = {
            .bfType = BF_TYPE,
            .bfileSize = get_image_size(image) + sizeof(struct bmp_header),
            .bOffBits = sizeof(struct bmp_header),
            .biSize = BI_SIZE,
            .biWidth = image->width,
            .biHeight = image->height,
            .biPlanes = 1,
            .biBitCount = BIT_COUNT,
            .biSizeImage = get_image_size(image)
    };

    return header;
}

enum read_status check_bmp(const struct bmp_header header){
    if (header.bfType != BF_TYPE) {
        return READ_INVALID_SIGNATURE;
    }
    if (header.biBitCount != BIT_COUNT) {
        return READ_INVALID_BITS;
    }
    if (header.biSize != BI_SIZE || header.biCompression != 0 || (header.bfileSize != header.bOffBits + header.biSizeImage)) {
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

enum read_status from_bmp( FILE* file, struct image* const image){
    if (!file) return READ_ERROR;
    struct bmp_header header;
    fread(&header, 1, sizeof(struct bmp_header), file);
    enum read_status status = check_bmp(header);
    *image = create_image(header.biHeight, header.biWidth);
    if (!status){
        for (uint32_t i = 0; i < header.biHeight ; i++) {
            if (fread(image->data + i * image->width, sizeof(struct pixel), image->width, file) < image->width) return READ_ERROR;;
            fseek(file, get_padding(image->width), SEEK_CUR);
        }
    }
    return status;
}

enum write_status to_bmp( FILE* file, struct image* const image ){
    if (!file) return WRITE_ERROR;
    if (!image) return WRITE_ERROR;
    struct bmp_header header = create_header(image);
    if (!fwrite(&header, sizeof(struct bmp_header), 1, file)) return WRITE_ERROR;
    uint8_t padding = get_padding(image->width);
    char padding_char = 0x00;
    for (uint32_t i = 0; i < image->height; i++) {
        if (fwrite(image->data + i * image ->width, sizeof(struct pixel), image->width, file) < image->width) return WRITE_ERROR;
        for (uint8_t j = 0; j < padding; j++) {
            if (fwrite(&padding_char, sizeof(char), 1, file) < 1) return WRITE_ERROR;
        }
    }
    return WRITE_OK;
}
