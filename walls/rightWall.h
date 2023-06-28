//
// Created by Andrei Goje on 16.06.23.
//

#ifndef LAB_3_RIGHTWALL_H
#define LAB_3_RIGHTWALL_H

class rightWall {

public:
    double y_min{}, y_max{}, z_min{}, z_max{}, position_on_axis{};

    rightWall(double yMin, double yMax, double zMin, double zMax, double positionOnAxis) : y_min(yMin), y_max(yMax),
                                                                                           z_min(zMin), z_max(zMax),
                                                                                           position_on_axis(
                                                                                                   positionOnAxis) {}

    rightWall() = default;

    double infinity = 1.79769e+308;

    rightWall &operator=(const rightWall &other) = default;

    bool hit(const ray &ray, hit_information &hit_info) const {
        double distance_from_wall_to_ray_origin = position_on_axis - ray.origin().x();
        double ray_travel_distance = distance_from_wall_to_ray_origin / ray.direction().x();

        if (ray_travel_distance < 0 || ray_travel_distance > infinity) return false;

        double y = ray.origin().y() + ray_travel_distance * ray.direction().y();
        double z = ray.origin().z() + ray_travel_distance * ray.direction().z();

        if (y < y_min || y > y_max || z < z_min || z > z_max) return false;

        hit_info.set_face_normal(ray, vec3(1, 0, 0));
        hit_info.hitPoint = ray.at(ray_travel_distance);
        return true;
    }
};

#endif //LAB_3_RIGHTWALL_H
