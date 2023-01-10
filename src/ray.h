#ifndef RAY_H
#define RAY_H

#include "vec.h"

typedef struct ray {
    point orig;
    vec3 dir;
} ray;

point ray_at(ray r, double t);

#endif