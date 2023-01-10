#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdlib.h>

extern const double infinity;
extern const double pi;  // 3.1415926535897932385

double degrees_to_radians(double degrees);

double random_double(void);

double random_double_range(double min, double max);

double clamp(double x, double min, double max);

#include "../lcdlib/ili934x.h"
#include "../lcdlib/lcd.h"
#include "ray.h"
#include "vec.h"

#endif