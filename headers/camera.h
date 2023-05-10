//
// Created by Andrei Goje on 08.05.23.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera {
public:

    double aspect_ration = 16.0/9.0;
    double viewport_height = 2.0;
    double viewport_width = aspect_ration * viewport_height;
    double focal_length = 1.0;

    camera() {
        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

inline double clamp(double x, double min, double max){
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif
