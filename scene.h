//
// Created by Andrei Goje on 18.05.23.
//

#ifndef LAB_3_SCENE_H
#define LAB_3_SCENE_H

#include <utility>
#include <vector>
#include "scene/camera.h"
#include "scene/Sphere.h"
#include "scene/light.h"
#include "scene/mesh.h"

class Scene {

private:
    color background_color;
    camera cam;
    std::vector<Sphere> scene_spheres;
    Light light;
    Mesh mesh;


public:
    Scene() = default;

    Scene(color background_color, camera cam, std::vector<Sphere> spheres, Light light, Mesh i_mesh)
            : background_color(background_color), cam(cam), scene_spheres(std::move(spheres)), light(std::move(light)),
              mesh(std::move(i_mesh)) {}

    bool ray_hit_object_in_scene(){}

    int get_image_width() {
        return static_cast<int>(cam.get_image_width());
    }

    int get_image_height() {
        return static_cast<int>(cam.get_image_height());
    }

    ray get_camera_ray(double u, double v) const {
        return cam.get_ray(u, v);
    }

    int get_max_depth() const {
        return cam.get_max_bounces();
    }

    std::vector<Sphere> get_scene_spheres() const {
        return scene_spheres;
    }

    Mesh get_mesh() {
        return mesh;
    }

    color get_background_color() const {
        return background_color;
    }

    Light get_light() const {
        return light;
    }

};


#endif //LAB_3_SCENE_H
