#ifndef VEC_H
#define VEC_H

#include <math.h>

#include "../lcdlib/ili934x.h"
#include "../lcdlib/lcd.h"

typedef struct vec3 {
    double x;
    double y;
    double z;
} vec3, point, colour;

vec3 add_vec3(vec3 v1, vec3 v2);
vec3 subtract_vec3(vec3 v1, vec3 v2);
vec3 multiply_vec3(vec3 v1, double t);
vec3 multiply_two_vec3(vec3 v1, vec3 v2);
vec3 divide_vec3(vec3 v1, double t);
double length_squared(vec3 v1);
double length(vec3 v1);
double dot_vec3(vec3 v1, vec3 v2);
vec3 cross_vec3(vec3 v1, vec3 v2);
vec3 unit_vec3(vec3 v);
vec3 random_vec3(void);
vec3 random_vec3_range(double min, double max);
vec3 random_in_unit_sphere(void);
vec3 random_unit_vec3(void);
vec3 random_in_hemisphere(vec3 normal);
uint8_t near_zero(vec3 v);
vec3 reflect(vec3 v, vec3 n);
vec3 refract(vec3 uv, vec3 n, double etai_over_etat);
vec3 random_in_unit_disk(void);

#endif