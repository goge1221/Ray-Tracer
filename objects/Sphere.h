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

    double get_radius() const { return radius; }

    point3 get_position() const { return position; }

    Material get_material() const { return material; };

    bool hit_by_ray(const ray& r, double t_min, double t_max, hit_information& hit_information) const{
        vec3 oc = r.origin() - position;
        double a = r.direction().length_squared();
        double half_b = dot(oc, r.direction());
        double c = oc.length_squared() - radius*radius;

        auto discriminant = half_b * half_b - a*c;
        if (discriminant < 0) return false;

        //Find the nearest root that lies in the acceptable range
        double root = (-half_b - sqrt(discriminant)) / a;
        double positive_root = (-half_b + sqrt(discriminant)) / a;
        if (!root_is_in_range(root, positive_root, t_min, t_max)) return false;

        hit_information.t = root;
        hit_information.hitPoint = r.at(root);

        vec3 outward_normal = (hit_information.hitPoint - position) / radius;
        hit_information.set_face_normal(r, outward_normal);

        return true;
    }

    bool root_is_in_range(double root, double positive_root, double t_min, double t_max) const{
        if (root < t_min || root > t_max){
            if (positive_root < t_min || positive_root > t_max)
                return false;
        }
        return true;
    }

};


#endif
