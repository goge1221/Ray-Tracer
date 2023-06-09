//
// Created by Andrei Goje on 08.05.23.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

class camera {

private:
    point3 camera_position;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 up;
    vec3 look_at;
    double camera_angle = 40.0;
    double image_width = 200;
    double image_height = 200;
    double aspect_ratio = 5.0;
    double viewport_height = 0.0;
    double viewport_width = 0.0;
    double pi = 3.1415926535897932385;

public:

    ray get_ray(double u, double v) const {
        return {camera_position, lower_left_corner + u*horizontal + v*vertical - camera_position};
    }

    void initialize_camera(double horizontal_res, double vertical_res){
        aspect_ratio = horizontal_res / vertical_res;
        image_width = horizontal_res;
        image_height = vertical_res;

        auto theta = camera_angle * pi / 180.0;
        auto h = tan(theta);
        viewport_width = 2.0 * h;
        viewport_height = viewport_width / aspect_ratio;

        vec3 camera_to_look_at_vec = normalize(camera_position - look_at);
        vec3 h_direction = normalize(cross(up, camera_to_look_at_vec));
        vec3 v_direction = cross(camera_to_look_at_vec, h_direction);

        horizontal = viewport_width * h_direction;
        vertical = viewport_height * v_direction;
        lower_left_corner = camera_position - horizontal/2 - vertical/2 - camera_to_look_at_vec;
    }


    void set_position(point3& received_camera_position){
        camera_position = received_camera_position;
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

    double get_image_width() const{
        return image_width;
    }

    double get_image_height() const{
        return image_height;
    }

};

#endif
