#include "camera.h"

camera create_camera(point lookfrom, point lookat, vec3 vup, double vfov,
                     double aspect_ratio, double aperture) {
    const double focus_dist = length(subtract_vec3(lookfrom, lookat));
    const double theta = degrees_to_radians(vfov);
    const double h = tan(theta / 2);
    const double viewport_height = 2.0 * h;
    const double viewport_width = aspect_ratio * viewport_height;

    const vec3 w = unit_vec3(subtract_vec3(lookfrom, lookat));
    const vec3 u = unit_vec3(cross_vec3(vup, w));
    const vec3 v = cross_vec3(w, u);

    const vec3 horizontal = multiply_vec3(u, viewport_width * focus_dist);
    const vec3 vertical = multiply_vec3(v, viewport_height * focus_dist);
    const point lower_left_corner = subtract_vec3(
        subtract_vec3(subtract_vec3(lookfrom, divide_vec3(horizontal, 2)),
                      divide_vec3(vertical, 2)),
        multiply_vec3(w, focus_dist));

    const camera c = {lookfrom, horizontal, vertical, lower_left_corner,
                      u,        v,          w,        aperture / 2};
    return c;
}

ray get_ray(const camera* c, double u, double v) {
    const vec3 rd = multiply_vec3(random_in_unit_disk(), c->lens_radius);
    const vec3 offset =
        add_vec3(multiply_vec3(c->u, rd.x), multiply_vec3(c->v, rd.y));
    return (ray){
        add_vec3(c->origin, offset),
        subtract_vec3(
            subtract_vec3(add_vec3(add_vec3(c->lower_left_corner,
                                            multiply_vec3(c->horizontal, u)),
                                   multiply_vec3(c->vertical, v)),
                          c->origin),
            offset)};
}