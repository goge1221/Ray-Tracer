//
// Created by Andrei Goje on 18.05.23.
//

#ifndef LAB_3_SCENE_H
#define LAB_3_SCENE_H

#include <utility>
#include <vector>
#include "headers/camera.h"
#include "objects/Sphere.h"
#include "objects/light.h"

class Scene {

private:
    color background_color;
    camera cam;
    std::vector<Sphere> scene_spheres;
    Light light;


public:
    Scene() = default;
    Scene(color background_color, camera cam, std::vector<Sphere> spheres, Light light)
            : background_color(background_color), cam(cam), scene_spheres(std::move(spheres)), light(light) {}

    int get_image_width(){
        return static_cast<int>(cam.get_image_width());
    }

    int get_image_height(){
        return static_cast<int>(cam.get_image_height());
    }

    ray get_camera_ray(double u, double v){
        return cam.get_ray(u, v);
    }

    std::vector<Sphere> get_scene_spheres(){
        return scene_spheres;
    }

    color get_background_color(){
        return background_color;
    }

    Light get_light(){
        return light;
    }

};


#endif //LAB_3_SCENE_H
