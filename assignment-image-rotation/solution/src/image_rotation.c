//
// Created by Daniil Kravchenko on 16.01.2022.
//

#include "../include/image_rotation.h"

struct image rotate(struct image* const source){
    struct image rotated_image = create_image(source->width, source->height);
    for (uint32_t i = 0; i < rotated_image.width; i++) {
        for (uint32_t j = 0; j < rotated_image.height; j++) {
            struct pixel pixel = get_pixel(source, i, j);
            set_pixel(&rotated_image, pixel, j, rotated_image.width - i - 1);
        }
    }
    return rotated_image;
}
