#include "colour.h"

void draw_line(uint16_t* buffer, uint8_t line) {
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(0);
    write_data16(display.width - 1);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(line);
    write_data16(line);
    write_cmd(MEMORY_WRITE);
    for (uint16_t x = 0; x <= display.width - 1; x++) write_data16(buffer[x]);
}

uint16_t to_rgb555(colour pixel_colour, uint8_t samples_per_pixel) {
    const double scale = 1.0 / samples_per_pixel;
    const uint8_t r =
        (uint8_t)(256 * clamp(sqrt(pixel_colour.x * scale), 0, 0.999));
    const uint8_t g =
        (uint8_t)(256 * clamp(sqrt(pixel_colour.y * scale), 0, 0.999));
    const uint8_t b =
        (uint8_t)(256 * clamp(sqrt(pixel_colour.z * scale), 0, 0.999));
    return (((r >> 3) & 0x1f) << 11 | ((g >> 2) & 0x3f) << 5 | (b >> 3) & 0x1f);
}