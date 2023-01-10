#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "sphere.h"

typedef struct hittable_list {
    uint8_t length;
    sphere* list[];
} hittable_list;

uint8_t hittable_list_hit(const hittable_list* h, ray r, double t_min,
                          double t_max, hit_record* rec);
hittable_list* create_list(uint8_t len);

#endif