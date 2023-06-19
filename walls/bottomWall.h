//
// Created by Andrei Goje on 19.06.23.
//

#ifndef LAB_3_BOTTOMWALL_H
#define LAB_3_BOTTOMWALL_H


#include "../headers/ray.h"
#include "../objects/hit_informations.h"

class bottomWall{

public:
    bottomWall(double _x0, double _x1, double _z0, double _z1, double _k)
            : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k){};

    double x0, x1, z0, z1, k;
    const double infinity = 1.79769e+308;


    bool hit(const ray& r, hit_information& rec) const {
        auto t = (k-r.origin().y()) / r.direction().y();
        if (t < 0 || t > infinity)
            return false;
        auto x = r.origin().x() + t*r.direction().x();
        auto z = r.origin().z() + t*r.direction().z();
        if (x < x0 || x > x1 || z < z0 || z > z1)
            return false;
        rec.u = (x-x0)/(x1-x0);
        rec.v = (z-z0)/(z1-z0);
        rec.t = t;
        auto outward_normal = vec3(0, 1, 0);
        rec.normal = outward_normal;
        rec.hitPoint = r.at(t);
        return true;
    }
};
#endif //LAB_3_BOTTOMWALL_H
