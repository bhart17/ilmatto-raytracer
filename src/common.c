#include "common.h"

const double infinity = INFINITY;
const double pi = 3.1415926535897932385f;

double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

// Returns a random real in [0,1).
double random_double(void) { return rand() / (RAND_MAX + 1.0); }

// Returns a random real in [min,max).
double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}