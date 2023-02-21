//
// Created by Daniil Kravchenko on 16.01.2022.
//

#include "../include/image.h"

struct image create_image(uint64_t height, uint64_t width) {
    return (struct image) {height, width, malloc(height * width * sizeof(struct pixel))};
}

void destroy_image(struct image* image){
    if(image){
        image->height = 0;
        image->width = 0;
        free(image->data);
    }
}

uint8_t get_padding(const uint64_t width){
    return (4 - (width * sizeof(struct pixel)) % 4) % 4;
}

uint8_t get_image_size(struct image* const image){
    return (get_padding(image->width) + image->height * image->width * sizeof(struct pixel));
}

struct pixel get_pixel(struct image* const image, uint64_t height, uint64_t width){
    size_t pixel_index = height * image->width + width;
    return image->data[pixel_index];
}

void set_pixel(struct image* const image, struct pixel pixel, uint64_t height, uint64_t width){
    image->data[height * image->width + width] = pixel;
}
