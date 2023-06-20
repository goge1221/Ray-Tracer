//
// Created by Andrei Goje on 16.06.23.
//

#ifndef LAB_3_RIGHTWALL_H
#define LAB_3_RIGHTWALL_H

#include "../headers/ray.h"
#include "../objects/hit_informations.h"

class rightWall{

public:
    double y_min{}, y_max{}, z_min{}, z_max{}, position_on_axis{};

    rightWall(double yMin, double yMax, double zMin, double zMax, double positionOnAxis) : y_min(yMin), y_max(yMax),
                                                                                           z_min(zMin), z_max(zMax),
                                                                                           position_on_axis(
                                                                                                   positionOnAxis) {}

    const double infinity = 1.79769e+308;

    bool hit(const ray& ray, hit_information& hit_info) const {
        auto t = (position_on_axis-ray.origin().x()) / ray.direction().x();
        if (t < 0 || t > infinity)
            return false;
        auto y = ray.origin().y() + t*ray.direction().y();
        auto z = ray.origin().z() + t*ray.direction().z();
        if (y < y_min || y > y_max || z < z_min || z > z_max)
            return false;
        hit_info.normal = vec3(1, 0, 0);
        hit_info.hitPoint = ray.at(t);
        return true;
    }
};

#endif //LAB_3_RIGHTWALL_H
