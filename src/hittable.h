#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.h"

typedef struct material {
    const enum type { lambertian, metal, dielectric } type;
    const colour albedo;
    const double fuzz;
    const double ir;
} material;

typedef struct hit_record {
    point p;
    vec3 normal;
    double t;
    uint8_t front_face;
    const material* mat;
} hit_record;

uint8_t scatter(const material* m, ray r_in, hit_record rec,
            colour* attenuation, ray* scattered);
void set_face_normal(hit_record* h, ray r, vec3 outward_normal);

#endif