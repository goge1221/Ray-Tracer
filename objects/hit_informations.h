//
// Created by Andrei Goje on 17.05.23.
//

#ifndef HIT_INFORMATIONS_H
#define HIT_INFORMATIONS_H

#include "../headers/ray.h"

struct hit_information{
    point3 hitPoint;
    vec3 normal;

    void set_face_normal(const ray& ray, const vec3& i_normal) {
        bool inside = dot(ray.direction(), i_normal) < 0;
        normal = inside ? i_normal : -i_normal;
    }
};

#endif //HIT_INFORMATIONS_H

