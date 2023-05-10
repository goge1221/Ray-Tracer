//
// Created by Andrei Goje on 08.05.23.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

class camera {
public:

    double aspect_ratio = 0.0;
    double viewport_height = 2.0;
    double viewport_width = 0.0;
    double focal_length = 1.0;

    camera()= default;

    ray get_ray(double u, double v) const {
        return {origin, lower_left_corner + u*horizontal + v*vertical - origin};
    }

    void set_position(vec3& camera_position){
        position = camera_position;
    }

    void set_look_at(vec3& look_at_input){
        look_at = look_at_input;
    }

    void set_up_position(vec3& up_position){
        up = up_position;
    }

    void set_camera_angle(double angle){
        camera_angle = angle;
    }

    void initialize_camera(double horizontal_res, double vertical_res){
        aspect_ratio = horizontal_res / vertical_res;
        viewport_width = aspect_ratio * viewport_height;
        image_width = horizontal_res;
        image_height = vertical_res;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    }

    double get_image_width() const{
        return image_width;
    }

    double get_image_height() const{
        return image_height;
    }



private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 up;
    vec3 position;
    vec3 look_at;
    double camera_angle;
    double image_width;
    double image_height;

};

inline double clamp(double x, double min, double max){
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif
