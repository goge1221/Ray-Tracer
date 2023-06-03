//
// Created by Andrei Goje on 11.05.23.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "../headers/vec3.h"
#include "material.h"
#include "hit_informations.h"

class Sphere {

private:
    double radius;
    point3 position;
    Material material;

public:
    Sphere(double radius, const point3 &position, Material material) : radius(radius), position(position),
                                                                       material(material) {}

    Material get_material() const { return material; };

    bool hit_by_ray(const ray &ray, hit_information &hit_information) const {
        vec3 directionVector = ray.origin() - position;
        double a = dot(ray.direction(), ray.direction());
        double half_b = dot(directionVector, ray.direction());
        double c = dot(directionVector, directionVector) - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;

        hit_information.discriminant = discriminant;
        hit_information.radius = radius;

        //Find the nearest root that lies in the acceptable range
        double root = (-half_b - sqrt(discriminant)) / a;

        hit_information.t = root;
        hit_information.hitPoint = ray.at(root);

        vec3 normal = (hit_information.hitPoint - position) / radius;
        hit_information.normal = normal;

        return true;
    }

    bool operator==(const Sphere &otherSphere) const {
        return otherSphere.position == this->position;
    }

    bool operator!=(const Sphere &otherSphere) const {
        return !operator==(otherSphere);
    }

};


#endif
