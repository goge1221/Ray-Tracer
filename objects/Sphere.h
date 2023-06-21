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
    int id;
    double radius;
    point3 position;
    Material material;
    const double infinity = 1.79769e+308;

public:
    Sphere(double radius, const point3 &position, Material material, int id) : radius(radius), position(position),
                                                                               material(material), id(id) {}

    Material get_material() const { return material; };

    bool hit_by_ray(const ray &ray, hit_information &hit_information) const {
        vec3 directionVector = ray.origin() - position;
        double a = dot(ray.direction(), ray.direction());
        double b = 2.0 * dot(directionVector, ray.direction());
        double c = dot(directionVector, directionVector) - radius * radius;

        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return false;

        double sqrtDiscriminant = sqrt(discriminant);
        double root = (-b - sqrtDiscriminant) / (2.0 * a);

        if (!root_is_in_range(root)) {
            root = (-b + sqrtDiscriminant) / (2.0 * a);
            if (!root_is_in_range(root))
                return false;
        }

        hit_information.hitPoint = ray.at(root);
        hit_information.set_face_normal(ray, (hit_information.hitPoint - position) / radius);
        return true;
    }

    bool root_is_in_range(double root) const {
        return (root > 0 && root < infinity);
    }

    bool operator==(const Sphere &otherSphere) const {
        return otherSphere.id == this->id;
    }

    bool operator!=(const Sphere &otherSphere) const {
        return !operator==(otherSphere);
    }

};


#endif
