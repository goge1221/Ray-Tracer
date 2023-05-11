//
// Created by Andrei Goje on 11.05.23.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "../headers/vec3.h"

class Sphere {

public:
    Sphere(double radius, const point3 &position) : radius(radius), position(position) {}

    double get_radius() const { return radius; }

    point3 get_position() const { return position; }


private:
    double radius;
    point3 position;
};


#endif
