//
// Created by Andrei Goje on 11.05.23.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "../utils/vec3.h"
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

/**
 * Determines if a ray intersects with the sphere and calculates intersection details.
 *
 * @param ray The incoming ray to test for intersection with the sphere.
 * @param hit_information A reference to a hit_information struct to be filled out with intersection details if there is a hit.
 * @param max_distance The maximum distance at which an intersection is considered valid.
 * @return true if the ray intersects the sphere within the specified range; false otherwise.
 */
    bool hit_by_ray(const ray &ray, hit_information &hit_information, double max_distance) const {
        // Calculate the vector from the ray origin to the sphere's position.
        vec3 directionVector = ray.origin() - position;

        // Compute the coefficients of the quadratic equation derived from the ray-sphere intersection formula.
        double a = dot(ray.direction(), ray.direction());
        double b = 2.0 * dot(directionVector, ray.direction());
        double c = dot(directionVector, directionVector) - radius * radius;

        // Calculate the discriminant to check if there is an intersection.
        double discriminant = b * b - 4 * a * c;

        // If the discriminant is negative, there are no real roots, and the ray does not intersect the sphere.
        if (discriminant < 0) return false;

        // Calculate the square root of the discriminant for further calculations.
        double sqrtDiscriminant = sqrt(discriminant);

        // Calculate the nearest root that lies in the acceptable range.
        double root = (-b - sqrtDiscriminant) / (2.0 * a);

        // Check if the first root is outside the valid range. If so, try the second root.
        if (!root_is_in_range(root, max_distance)) {
            root = (-b + sqrtDiscriminant) / (2.0 * a);
            if (!root_is_in_range(root, max_distance))
                return false; // If the second root is also invalid, return false.
        }

        // Calculate the hit point on the sphere using the valid root and update the hit_information.
        hit_information.hitPoint = ray.at(root);
        // Calculate and set the correct face normal at the hit point.
        hit_information.set_face_normal(ray, (hit_information.hitPoint - position) / radius);

        return true; // The ray hits the sphere, and the information is recorded.
    }

/**
 * Note: The method root_is_in_range is assumed to check if the calculated root value is within a specified range (0, max_distance).
 * The exact implementation details of root_is_in_range and the ray class's methods like origin, direction, and at are not provided here.
 */


    static bool root_is_in_range(double root, double max_shadow_distance) {
        return (root > 0.001 && root < max_shadow_distance);
    }

    bool operator==(const Sphere &otherSphere) const {
        return otherSphere.id == this->id;
    }

    bool operator!=(const Sphere &otherSphere) const {
        return !operator==(otherSphere);
    }

};



#endif
