#include <math.h>
#include <stdlib.h>

#include "camera.h"
#include "colour.h"
#include "common.h"
#include "hittable_list.h"
#include "sphere.h"

static colour ray_colour(ray r, const hittable_list* world, int8_t depth) {
    hit_record rec;

    if (depth <= 0) return (colour){0, 0, 0};

    if (hittable_list_hit(world, r, 0.001, INFINITY, &rec)) {
        ray scattered;
        colour attenuation;
        if (scatter(rec.mat, r, rec, &attenuation, &scattered)) {
            return multiply_two_vec3(attenuation,
                                     ray_colour(scattered, world, depth - 1));
        }
        return (colour){0, 0, 0};
    }

    // sky
    const vec3 unit_direction = unit_vec3(r.dir);
    const double t = 0.5 * (unit_direction.y + 1.0);
    return add_vec3(multiply_vec3((colour){1, 1, 1}, (1.0 - t)),
                    multiply_vec3((colour){0.5, 0.7, 1.0}, t));
}

int main(void) {
    const uint16_t image_width = 320;
    const uint16_t image_height = 240;
    const uint8_t samples_per_pixel = 3;
    const uint8_t max_depth = 10;

    const point lookfrom = {0, 0, 0};
    const point lookat = {0, 0, -1};
    const vec3 vup = {0, 1, 0};
    const double aperture = 0;

    const material material_ground = {lambertian,
                                      .albedo = (colour){0.8, 0.8, 0.0}};
    const material material_center = {lambertian,
                                      .albedo = (colour){0.1, 0.2, 0.5}};
    // const material material_left = {dielectric, .ir = 1.5};
    // const material material_right = {metal, .albedo = (colour){0.8, 0.6,
    // 0.2}, .fuzz = 0};

    // TODO: change this
    hittable_list* h = create_list(2);
    h->list[0] = &(sphere){(point){0, -100.5, -1}, 100, &material_ground};
    h->list[1] = &(sphere){(point){0, 0, -1}, 0.5, &material_center};
    // h->list[2] = &(sphere){(point){-1, 0, -1}, 0.5, &material_left};
    // h->list[2] = &(sphere){(point){0.5, 0, -1}, 0.5, &material_right};

    const camera cam = create_camera(
        lookfrom, lookat, vup, 90, (float)image_width / image_height, aperture);

    init_lcd();
    set_orientation(West);

    uint16_t pixel_buffer[image_width];

    for (int16_t j = image_height - 1; j >= 0; --j) {
        for (int16_t i = 0; i < image_width; ++i) {
            colour pixel_colour = {0, 0, 0};
            for (uint8_t s = 0; s < samples_per_pixel; ++s) {
                const double u = (i + random_double()) / (image_width - 1);
                const double v = (j + random_double()) / (image_height - 1);
                const ray r = get_ray(&cam, u, v);
                pixel_colour =
                    add_vec3(pixel_colour, ray_colour(r, h, max_depth));
            }
            pixel_buffer[i] = to_rgb555(pixel_colour, samples_per_pixel);
        }
        draw_line(pixel_buffer, j);
    }

    while (1)
        ;
}