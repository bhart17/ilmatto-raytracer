#include "sphere.h"

uint8_t sphere_hit(const sphere* s, ray r, double t_min, double t_max,
                   hit_record* rec) {
    const vec3 oc = subtract_vec3(r.orig, s->center);
    const double a = length_squared(r.dir);
    const double half_b = dot_vec3(oc, r.dir);
    const double c = length_squared(oc) - s->radius * s->radius;

    const double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return 0;
    const double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) return 0;
    }

    rec->t = root;
    rec->p = ray_at(r, rec->t);
    set_face_normal(rec, r,
                    divide_vec3(subtract_vec3(rec->p, s->center), s->radius));
    rec->mat = s->mat;

    return 1;
}