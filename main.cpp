#include <iostream>
#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/camera.h"
#include "parser/XMLParser.h"


color ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, Light light) {
    hit_information hitInformation;

    for (const auto &sphere: spheres) {
        if (sphere.hit_by_ray(camera_ray, hitInformation)) {

            vec3 lightVector = light.getParallelLightDirection();

            // Calculate the direction of the light ray.
            vec3 L = -unit_vector(lightVector);

            //Calculate the diffuse component
            color ambientColor = light.getAmbientLightColor();

            // Calculate the ambient component.
            vec3 ambient = ambientColor*sphere.get_material().getColor()*sphere.get_material().getKa();

            // Calculate the diffuse component.
            double Kd = dot(L, hitInformation.normal);
            if (Kd < 0) Kd = 0;

            vec3 diffuse = Kd * ambient;


            // Calculate the direction of the view ray.
            vec3 E = -unit_vector(hitInformation.hitPoint);

            // Calculate the half vector.
            vec3 H = unit_vector(L + E);

            // Calculate the specular component.
            double KsDot = dot(H, hitInformation.normal);
           // if (KsDot < 0) KsDot;

            double Ks = pow(KsDot, 200);
            if (Ks < 0) Ks = sphere.get_material().getKs();
            color paralelLightColor = light.getParallelLightColor();
            vec3 specular = Ks * paralelLightColor;

            // Return the sum of the ambient, diffuse, and specular components.
            return ambient + diffuse + specular;
        }
    }

    return background_color;
}


int main() {

    Scene scene;
    XMLParser xmlParser;
    xmlParser.load_xml_File("example2.xml", scene);

    int image_width = scene.get_image_width();
    int image_height = scene.get_image_height();

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray ray = scene.get_camera_ray(u, v);
            color pixel_color = ray_color(ray, scene.get_scene_spheres(),
                                          scene.get_background_color(), scene.get_light());
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}


