#include <iostream>
#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/camera.h"
#include "parser/XMLParser.h"

bool hit_something(const ray &ray, hit_information &hit_info, const std::vector<Sphere> &spheres) {
    hit_information temporary;
    bool hit_anything = false;
    double closest = 1000;

    for (const auto &sphere: spheres) {
        if (sphere.hit_by_ray(ray, 0, closest, temporary)) {
            hit_anything = true;
            closest = temporary.t;
            hit_info = temporary;
        }
    }
    return hit_anything;
}


color ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, int max_bounces) {
    hit_information hitInformation;

    if (max_bounces <= 0) return {0, 0, 0};

    if (hit_something(camera_ray, hitInformation, spheres)) {
        point3 target = hitInformation.hitPoint + hitInformation.normal;
        return spheres.at(0).get_material().getColor();
      //return ray_color(ray(hitInformation.hitPoint, target - hitInformation.hitPoint), spheres, background_color,
        //                 max_bounces - 1);
    }

    return {0.5, 0.5, 0.5};
}


int main() {

    XMLParser xmlParser;
    xmlParser.load_xml_File("example1.xml");

    camera cam = xmlParser.get_camera();
    std::vector<Sphere> spheres = xmlParser.get_scene_spheres();

    int image_width = static_cast<int>(cam.get_image_width());
    int image_height = static_cast<int>(cam.get_image_height());
    int max_bounces = cam.get_maximal_ray_bound();

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray ray = cam.get_ray(u, v);
            color pixel_color = ray_color(ray, spheres, xmlParser.get_background_color(), max_bounces);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}


