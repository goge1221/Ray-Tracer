//
// Created by Andrei Goje on 16.06.23.
//

#ifndef LAB_3_RIGHTWALL_H
#define LAB_3_RIGHTWALL_H

#include "../headers/ray.h"
#include "../objects/hit_informations.h"

class rightWall{

public:
    double y0{}, y1{}, z0{}, z1{}, k{};
    const double infinity = 1.79769e+308;

    rightWall() = default;

    rightWall(double _y0, double _y1, double _z0, double _z1, double _k)
            : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k){};


    bool hit(const ray& r, hit_information& rec) const {
        auto t = (k-r.origin().x()) / r.direction().x();
        if (t < 0 || t > infinity)
            return false;
        auto y = r.origin().y() + t*r.direction().y();
        auto z = r.origin().z() + t*r.direction().z();
        if (y < y0 || y > y1 || z < z0 || z > z1)
            return false;
        rec.u = (y-y0)/(y1-y0);
        rec.v = (z-z0)/(z1-z0);
        rec.t = t;
        auto outward_normal = vec3(1, 0, 0);
        rec.normal = outward_normal;
        rec.hitPoint = r.at(t);
        return true;
    }
};

#endif //LAB_3_RIGHTWALL_H
