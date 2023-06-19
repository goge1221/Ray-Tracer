//
// Created by Andrei Goje on 19.06.23.
//

#ifndef LAB_3_BEHINDWALL_H
#define LAB_3_BEHINDWALL_H

#include "../headers/ray.h"
#include "../objects/hit_informations.h"

class behindWall{
public:
    double x0, x1, y0, y1, k;
    const double infinity = 1.79769e+308;

    behindWall() = default;

    behindWall(double _x0, double _x1, double _y0, double _y1, double _k)
            : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k) {};


    bool hit(const ray& r, hit_information& rec) const {
        auto t = (k-r.origin().z()) / r.direction().z();
        if (t < 0 || t > infinity)
            return false;
        auto x = r.origin().x() + t*r.direction().x();
        auto y = r.origin().y() + t*r.direction().y();
        if (x < x0 || x > x1 || y < y0 || y > y1)
            return false;
        rec.u = (x-x0)/(x1-x0);
        rec.v = (y-y0)/(y1-y0);
        rec.t = t;
        auto outward_normal = vec3(0, 0, 1);
        rec.normal = outward_normal;
        rec.hitPoint = r.at(t);
        return true;
    }

};

#endif //LAB_3_BEHINDWALL_H
