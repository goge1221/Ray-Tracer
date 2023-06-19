//
// Created by Andrei Goje on 16.06.23.
//

#ifndef LAB_3_SQUARE_H
#define LAB_3_SQUARE_H

#include "../headers/ray.h"
#include "hit_informations.h"

class Square{
public:
    Square() = default;
    double m_x0, m_x1, m_y0, m_y1, m_k;

    Square(double x0, double x1, double y0, double y1, double k)
            :  m_x0(x0), m_x1(x1), m_y0(y0), m_y1(y1), m_k(k){};

    static bool hit_by_ray(const ray& ray, hit_information& hit_info) {
        const double t_min = 0.001;  // Minimum distance along the ray to consider
        const double t_max = std::numeric_limits<double>::infinity();

        // Define the Cornell box walls
        // Each wall is represented by an infinite plane with its normal and a point on the plane

        // Floor (Y-Z plane)
        if (hit_plane(ray, vec3(0.0, 1.0, 0.0), vec3(0.0, -2.0, 0.0), t_min, t_max, hit_info)) {
            hit_info.normal = vec3(0.0, 1.0, 0.0);  // Surface normal of the floor
            return true;
        }

        // Ceiling (Y-Z plane)
        if (hit_plane(ray, vec3(0.0, -1.0, 0.0), vec3(0.0, 2.0, 0.0), t_min, t_max, hit_info)) {
            hit_info.normal = vec3(0.0, -1.0, 0.0);  // Surface normal of the ceiling
            return true;
        }

        // Left wall (X-Z plane)
        if (hit_plane(ray, vec3(1.0, 0.0, 0.0), vec3(-2.0, 0.0, 0.0), t_min, t_max, hit_info)) {
            hit_info.normal = vec3(1.0, 0.0, 0.0);  // Surface normal of the left wall
            return true;
        }

        // Right wall (X-Z plane)
        if (hit_plane(ray, vec3(-1.0, 0.0, 0.0), vec3(2.0, 0.0, 0.0), t_min, t_max, hit_info)) {
            hit_info.normal = vec3(-1.0, 0.0, 0.0);  // Surface normal of the right wall
            return true;
        }

        // Back wall (X-Y plane)
        if (hit_plane(ray, vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, -5.0), t_min, t_max, hit_info)) {
            hit_info.normal = vec3(0.0, 0.0, 1.0);  // Surface normal of the back wall
            // return true;
        }

        // Front wall (X-Y plane)
        if (hit_plane(ray, vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, 5.0), t_min, t_max, hit_info)) {
            hit_info.normal = vec3(0.0, 0.0, -1.0);  // Surface normal of the front wall
            return true;
        }

        return false;  // No intersection with any wall
    }


    static bool hit_plane(const ray& ray, const vec3& normal, const vec3& point, double t_min, double t_max, hit_information& hit_info) {
        double denominator = dot(ray.direction(), normal);
        if (denominator != 0.0) {
            double t = dot(point - ray.origin(), normal) / denominator;
            if (t >= t_min && t <= t_max) {
                hit_info.hitPoint = ray.at(t);
                return true;
            }
        }
        return false;
    }


};

#endif //LAB_3_SQUARE_H
