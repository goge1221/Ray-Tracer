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

public:
    Sphere(double radius, const point3 &position, Material material, int id) : radius(radius), position(position),
                                                                       material(material), id(id) {}

    Material get_material() const { return material; };

    bool hit_by_ray(const ray &ray, double t_min, double t_max, hit_information &hit_information) const {
        vec3 directionVector = ray.origin() - position;
        double a = dot(ray.direction(), ray.direction());
        double b = 2.0 * dot(directionVector, ray.direction());
        double c = dot(directionVector, directionVector) - radius * radius;

        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return false;

        hit_information.discriminant = discriminant;
        hit_information.radius = radius;

        // Find the nearest root that lies in the acceptable range
        double sqrtDiscriminant = sqrt(discriminant);
        double root = (-b - sqrtDiscriminant) / (2.0 * a);
        if (root < t_min || root > t_max) {
            root = (-b + sqrtDiscriminant) / (2.0 * a);
            if (root < t_min || root > t_max)
                return false;
        }

        hit_information.t = root;
        hit_information.hitPoint = ray.at(root);

        vec3 outward_normal = (hit_information.hitPoint - position) / radius;
        hit_information.set_face_normal(ray, outward_normal);

        return true;
    }


    bool operator==(const Sphere &otherSphere) const {
        return otherSphere.id == this->id;
    }

    bool operator!=(const Sphere &otherSphere) const {
        return !operator==(otherSphere);
    }

};


#endif
