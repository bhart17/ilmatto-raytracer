#ifndef COLOUR_H
#define COLOUR_H

#include "common.h"

void draw_line(uint16_t* buffer, uint8_t line);
uint16_t to_rgb555(colour pixel_colour, uint8_t samples_per_pixel);

#endif