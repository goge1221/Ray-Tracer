//
// Created by Andrei Goje on 19.06.23.
//

#ifndef LAB_3_BOTTOMWALL_H
#define LAB_3_BOTTOMWALL_H

class bottomWall {

public:

    double x_min{}, x_max{}, z_min{}, z_max{}, position_on_axis{};

    bottomWall(double xMin, double xMax, double zMin, double zMax, double positionOnAxis) : x_min(xMin), x_max(xMax),
                                                                                            z_min(zMin), z_max(zMax),
                                                                                            position_on_axis(
                                                                                                    positionOnAxis) {}

    bottomWall() = default;
    bottomWall& operator=(const bottomWall& other) = default;

    double infinity = 1.79769e+308;

    bool hit(const ray &ray, hit_information &hit_info) const {
        double distance_from_wall_to_ray_origin = position_on_axis - ray.origin().y();
        double ray_travel_distance = distance_from_wall_to_ray_origin / ray.direction().y();

        if (ray_travel_distance < 0 || ray_travel_distance > infinity) return false;

        double x = ray.origin().x() + ray_travel_distance * ray.direction().x();
        double z = ray.origin().z() + ray_travel_distance * ray.direction().z();

        if (x < x_min || x > x_max || z < z_min || z > z_max) return false;

        hit_info.set_face_normal(ray, vec3(0, 1, 0));
        hit_info.hitPoint = ray.at(ray_travel_distance);
        return true;
    }
};

#endif //LAB_3_BOTTOMWALL_H
