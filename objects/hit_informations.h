//
// Created by Andrei Goje on 17.05.23.
//

#ifndef HIT_INFORMATIONS_H
#define HIT_INFORMATIONS_H

#include "../headers/ray.h"

struct hit_information{

    point3 hitPoint;
    vec3 normal;
    double radius{};
    double t{};
    double discriminant{};
    bool front_face{};

    inline void set_face_normal(const ray& ray, const vec3& outward_normal){
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};

#endif //HIT_INFORMATIONS_H

