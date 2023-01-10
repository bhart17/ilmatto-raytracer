#include "ray.h"

point ray_at(ray r, double t) {
    return (point)add_vec3(r.orig, multiply_vec3(r.dir, t));
}