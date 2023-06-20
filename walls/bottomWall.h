//
// Created by Andrei Goje on 19.06.23.
//

#ifndef LAB_3_BOTTOMWALL_H
#define LAB_3_BOTTOMWALL_H


#include "../headers/ray.h"
#include "../objects/hit_informations.h"

class bottomWall{

public:

    double x_min{}, x_max{}, z_min{}, z_max{}, position_on_axis{};

    bottomWall(double xMin, double xMax, double zMin, double zMax, double positionOnAxis) : x_min(xMin), x_max(xMax),
                                                                                            z_min(zMin), z_max(zMax),
                                                                                            position_on_axis(
                                                                                                    positionOnAxis) {}

    const double infinity = 1.79769e+308;

    bool hit(const ray& ray, hit_information& hit_info) const {
        auto t = (position_on_axis-ray.origin().y()) / ray.direction().y();
        if (t < 0 || t > infinity)
            return false;
        auto x = ray.origin().x() + t*ray.direction().x();
        auto z = ray.origin().z() + t*ray.direction().z();
        if (x < x_min || x > x_max || z < z_min || z > z_max)
            return false;
        hit_info.normal = vec3(0, 1, 0);
        hit_info.hitPoint = ray.at(t);
        return true;
    }
};
#endif //LAB_3_BOTTOMWALL_H
