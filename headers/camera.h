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
    int maximal_ray_bound = 0;

public:

    void set_maximal_ray_bound(int ray_bound){
        maximal_ray_bound = ray_bound;
    }

    int get_maximal_ray_bound(){
        return maximal_ray_bound;
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

        auto w = unit_vector(camera_position - look_at);
        auto u = unit_vector(cross(up, w));
        auto v = cross(w, u);

        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = camera_position - horizontal/2 - vertical/2 - w;

    }

    double get_image_width() const{
        return image_width;
    }

    double get_image_height() const{
        return image_height;
    }

};

#endif
