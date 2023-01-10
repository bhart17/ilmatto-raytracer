#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

typedef struct sphere {
    point center;
    double radius;
    const material* mat;
} sphere;

uint8_t sphere_hit(const sphere* s, ray r, double t_min, double t_max,
                   hit_record* rec);

#endif