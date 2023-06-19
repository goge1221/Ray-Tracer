//
// Created by Andrei Goje on 17.05.23.
//

#ifndef HIT_INFORMATIONS_H
#define HIT_INFORMATIONS_H

#include "../headers/ray.h"

struct hit_information{
    point3 hitPoint;
    vec3 normal;
    double u;
    double v;
    double t;
};

#endif //HIT_INFORMATIONS_H

