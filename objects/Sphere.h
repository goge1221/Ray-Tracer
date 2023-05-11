//
// Created by Andrei Goje on 11.05.23.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "../headers/vec3.h"
#include "material.h"

class Sphere {

private:
    double radius;
    point3 position;
    Material material;

public:
    Sphere(double radius, const point3 &position, Material material) : radius(radius), position(position),
                                                                       material(material) {}

    double get_radius() const { return radius; }

    point3 get_position() const { return position; }

    Material get_material() const { return material; };
};


#endif
