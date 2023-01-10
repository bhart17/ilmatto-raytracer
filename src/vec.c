#include "vec.h"

#include "common.h"

vec3 add_vec3(vec3 v1, vec3 v2) {
    return (vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

vec3 subtract_vec3(vec3 v1, vec3 v2) {
    return (vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

vec3 multiply_vec3(vec3 v1, double t) {
    return (vec3){v1.x * t, v1.y * t, v1.z * t};
}

vec3 multiply_two_vec3(vec3 v1, vec3 v2) {
    return (vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

vec3 divide_vec3(vec3 v1, double t) {
    return (vec3){v1.x / t, v1.y / t, v1.z / t};
}

double length_squared(vec3 v1) {
    return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
}

double length(vec3 v1) { return sqrt(length_squared(v1)); }

double dot_vec3(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 cross_vec3(vec3 v1, vec3 v2) {
    return (vec3){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x};
}

vec3 unit_vec3(vec3 v1) { return divide_vec3(v1, length(v1)); }

vec3 random_vec3(void) {
    return (vec3){random_double(), random_double(), random_double()};
}

vec3 random_vec3_range(double min, double max) {
    return (vec3){random_double_range(min, max), random_double_range(min, max),
                  random_double_range(min, max)};
}

vec3 random_in_unit_sphere(void) {
    while (1) {
        const vec3 p = random_vec3_range(-1, 1);
        if (length_squared(p) >= 1) continue;
        return p;
    }
}

vec3 random_unit_vec3(void) { return unit_vec3(random_in_unit_sphere()); }

vec3 random_in_hemisphere(vec3 normal) {
    const vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot_vec3(in_unit_sphere, normal) >
        0.0)  // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return subtract_vec3((vec3){0, 0, 0}, in_unit_sphere);
}

// Return true if the vector is close to zero in all dimensions.
uint8_t near_zero(vec3 v) {
    const double s = 1e-8;
    return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

vec3 reflect(vec3 v1, vec3 n) {
    return subtract_vec3(v1, multiply_vec3(n, 2 * dot_vec3(v1, n)));
}

vec3 refract(vec3 uv, vec3 n, double etai_over_etat) {
    const double cos_theta =
        fmin(dot_vec3(subtract_vec3((vec3){0, 0, 0}, uv), n), 1.0);
    const vec3 r_out_perp = multiply_vec3(
        add_vec3(uv, multiply_vec3(n, cos_theta)), etai_over_etat);
    const vec3 r_out_parallel =
        multiply_vec3(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
    return add_vec3(r_out_perp, r_out_parallel);
}

vec3 random_in_unit_disk(void) {
    while (1) {
        const vec3 p = {random_double_range(-1, 1), random_double_range(-1, 1),
                        0};
        if (length_squared(p) >= 1) continue;
        return p;
    }
}