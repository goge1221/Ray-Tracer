//
// Created by Andrei Goje on 19.06.23.
//

#ifndef LAB_3_BEHINDWALL_H
#define LAB_3_BEHINDWALL_H

#include "../headers/ray.h"
#include "../objects/hit_informations.h"

class behindWall{
public:
    double x_min{}, x_max{}, y_min{}, y_max{}, position_on_axis{};

    behindWall(double xMin, double xMax, double yMin, double yMax, double pointOnAxis) : x_min(xMin), x_max(xMax),
                                                                                         y_min(yMin), y_max(yMax),
                                                                                         position_on_axis(pointOnAxis) {}

    const double infinity = 1.79769e+308;

    bool hit(const ray& ray, hit_information& hit_info) const {
        auto t = (position_on_axis-ray.origin().z()) / ray.direction().z();
        if (t < 0 || t > infinity)
            return false;
        auto x = ray.origin().x() + t*ray.direction().x();
        auto y = ray.origin().y() + t*ray.direction().y();
        if (x < x_min || x > x_max || y < y_min || y > y_max)
            return false;
        hit_info.normal = vec3(0, 0, 1);
        hit_info.hitPoint = ray.at(t);
        return true;
    }

};

#endif //LAB_3_BEHINDWALL_H
