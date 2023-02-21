//
// Created by Daniil Kravchenko on 14.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_H

#include <inttypes.h>
#include <mm_malloc.h>

struct __attribute__((packed)) pixel { uint8_t b, g, r; };

struct image {
    uint64_t height, width;
    struct pixel* data;
};

struct image create_image(uint64_t height, uint64_t width);

void destroy_image(struct image* image);

uint8_t get_padding(uint64_t width);

uint8_t get_image_size(struct image* const image);

struct pixel get_pixel(struct image* const image, uint64_t height, uint64_t width);

void set_pixel(struct image* const image, struct pixel pixel, uint64_t height, uint64_t width);

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
