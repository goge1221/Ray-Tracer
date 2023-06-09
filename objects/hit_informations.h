//
// Created by Andrei Goje on 17.05.23.
//

#ifndef HIT_INFORMATIONS_H
#define HIT_INFORMATIONS_H

#include "../headers/ray.h"

struct hit_information{

    point3 hitPoint;
    vec3 normal;
    double t{};
    double discriminant{};
};

#endif //HIT_INFORMATIONS_H

