//
// Created by Andrei Goje on 19.06.23.
//

#ifndef LAB_3_BEHINDWALL_H
#define LAB_3_BEHINDWALL_H

class behindWall {
public:
    double x_min{}, x_max{}, y_min{}, y_max{}, position_on_axis{};

    behindWall(double xMin, double xMax, double yMin, double yMax, double pointOnAxis) : x_min(xMin), x_max(xMax),
                                                                                         y_min(yMin), y_max(yMax),
                                                                                         position_on_axis(
                                                                                                 pointOnAxis) {}

    behindWall &operator=(const behindWall &other) = default;

    behindWall() = default;

    double infinity = 1.79769e+308;

    bool hit(const ray &ray, hit_information &hit_info) const {
        double distance_from_wall_to_ray_origin = position_on_axis - ray.origin().z();
        double ray_travel_distance = distance_from_wall_to_ray_origin / ray.direction().z();

        if (ray_travel_distance < 0 || ray_travel_distance > infinity) return false;

        double x = ray.origin().x() + ray_travel_distance * ray.direction().x();
        double y = ray.origin().y() + ray_travel_distance * ray.direction().y();

        if (x < x_min || x > x_max || y < y_min || y > y_max) return false;

        hit_info.set_face_normal(ray, vec3(0, 0, 1));
        hit_info.hitPoint = ray.at(ray_travel_distance);
        return true;
    }

};

#endif //LAB_3_BEHINDWALL_H
