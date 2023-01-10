#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

typedef struct camera {
    point origin;
    vec3 horizontal;
    vec3 vertical;
    point lower_left_corner;
    vec3 u, v, w;
    double lens_radius;
} camera;

camera create_camera(point lookfrom, point lookat, vec3 vup, double vfov,
                     double aspect_ratio, double aperture);
ray get_ray(const camera* c, double u, double v);

#endif