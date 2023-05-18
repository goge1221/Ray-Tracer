#include <iostream>
#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/camera.h"
#include "parser/XMLParser.h"

vec3 reflect(vec3 v, vec3 n) {
    // Calculate the reflection vector.
    return v - 2.0 * dot(v, n) * n;
}

color ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, int max_bounces) {
    hit_information hitInformation;

    if (max_bounces <= 0) return {0, 0, 0};

    for (const auto &sphere: spheres) {
        if (sphere.hit_by_ray(camera_ray, hitInformation)) {

            vec3 lightVector(-3, 3, -1);

            // Calculate the direction of the light ray.
            vec3 L = -unit_vector(lightVector);

            //Calculate the diffuse component
            color ambientColor(1, 1, 1);

            // Calculate the ambient component.
            vec3 ambient = ambientColor*sphere.get_material().getColor()*sphere.get_material().getKa();

            // Calculate the diffuse component.
            double Kd = dot(L, hitInformation.normal);
            if (Kd < 0) Kd = 0.0;

            vec3 diffuse = Kd * ambient;


            // Calculate the direction of the view ray.
            vec3 E = -unit_vector(hitInformation.hitPoint);

            // Calculate the half vector.
            vec3 H = unit_vector(L + E);


            // Calculate the specular component.
            double KsDot = dot(H, hitInformation.normal);
            if (KsDot < 0) KsDot = 0;

            double Ks = pow(KsDot, 200);
            vec3 specular = Ks * color(1,1,1);

            // Return the sum of the ambient, diffuse, and specular components.
            return ambient + diffuse + specular;
        }
    }

    return {0, 0, 0};
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


