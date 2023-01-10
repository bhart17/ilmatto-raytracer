#include "hittable.h"

#include <stdio.h>

void set_face_normal(hit_record* h, ray r, vec3 outward_normal) {
    h->front_face = dot_vec3(r.dir, outward_normal) < 0;
    h->normal = h->front_face ? outward_normal
                              : subtract_vec3((vec3){0, 0, 0}, outward_normal);
}

// Schlick's approximation for reflectance
static double reflectance(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

uint8_t scatter(const material* m, ray r_in, hit_record rec,
                colour* attenuation, ray* scattered) {
    switch (m->type) {
        case lambertian: {
            vec3 scatter_direction = add_vec3(rec.normal, random_unit_vec3());
            if (near_zero(scatter_direction)) {
                scatter_direction = rec.normal;
            }
            *scattered = (ray){rec.p, scatter_direction};
            *attenuation = m->albedo;
            return 1;
        }
        case metal: {
            *scattered = (ray){
                rec.p,
                add_vec3(reflect(unit_vec3(r_in.dir), rec.normal),
                         multiply_vec3(random_in_unit_sphere(), m->fuzz))};
            *attenuation = m->albedo;
            return (dot_vec3(scattered->dir, rec.normal) > 0);
        }
        case dielectric: {
            *attenuation = (colour){1, 1, 1};

            const double refraction_ratio =
                rec.front_face ? (1.0 / m->ir) : m->ir;
            const vec3 unit_direction = unit_vec3(r_in.dir);
            const double cos_theta =
                fmin(dot_vec3(subtract_vec3((vec3){0, 0, 0}, unit_direction),
                              rec.normal),
                     1.0);
            const double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            vec3 direction;
            if (refraction_ratio * sin_theta > 1.0 ||
                reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                direction =
                    refract(unit_direction, rec.normal, refraction_ratio);

            *scattered = (ray){rec.p, direction};
            return 1;
        }
    }
}