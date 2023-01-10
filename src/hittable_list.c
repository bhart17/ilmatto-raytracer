#include "hittable_list.h"

#include <stdlib.h>

uint8_t hittable_list_hit(const hittable_list* h, ray r, double t_min,
                          double t_max, hit_record* rec) {
    hit_record temp_rec;
    uint8_t hit_anything = 0;
    double closest_so_far = t_max;

    for (uint8_t i = 0; i < h->length; i++) {
        if (sphere_hit(h->list[i], r, t_min, closest_so_far, &temp_rec)) {
            hit_anything = 1;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

hittable_list* create_list(uint8_t len) {
    hittable_list* h = malloc(sizeof(hittable_list*) + sizeof(sphere) * len);
    h->length = len;
    return h;
}
