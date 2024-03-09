//
// Created by Andrei Goje on 08.05.23.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../utils/ray.h"
#include "../utils/vec3.h"

class camera {

private:
    // Camera configuration variables
    point3 camera_position;
    point3 lower_left_corner; // The lower left corner of the camera's viewport.
    vec3 horizontal; // Vector defining the horizontal extent of the viewport.
    vec3 vertical; // Vector defining the vertical extent of the viewport.
    vec3 up; // Up direction for the camera, used to calculate orientation.
    vec3 look_at; // Point the camera is looking at.
    double camera_angle = 40.0; // Field of view angle of the camera.
    double image_width = 200;
    double image_height = 200;
    double aspect_ratio = 5.0;
    double viewport_height = 0.0; // Calculated height of the camera's viewport.
    double viewport_width = 0.0; // Calculated width of the camera's viewport.
    double pi = 3.1415926535897932385; // Pi constant for angle conversions.
    int max_bounces{};

public:

    ray get_ray(double u, double v) const {
        return {camera_position, lower_left_corner + u * horizontal + v * vertical - camera_position};
    }

    void initialize_camera(double horizontal_res, double vertical_res) {
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
        lower_left_corner = camera_position - horizontal / 2 - vertical / 2 - camera_to_look_at_vec;
    }


    /* GETTERS & SETTERS */
    void set_max_bounces(int v_max_bounces){
        this->max_bounces = v_max_bounces;
    }

    int get_max_bounces() const{
        return max_bounces;
    }

    void set_position(point3 &received_camera_position) {
        camera_position = received_camera_position;
    }

    void set_look_at(vec3 &look_at_input) {
        look_at = look_at_input;
    }

    void set_up_position(vec3 &up_position) {
        up = up_position;
    }

    void set_camera_angle(double angle) {
        camera_angle = angle;
    }

    double get_image_width() const {
        return image_width;
    }

    double get_image_height() const {
        return image_height;
    }

};

#endif
