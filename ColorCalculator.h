//
// Created by Andrei Goje on 18.05.23.
//

#ifndef COLORCALCULATOR_H
#define COLORCALCULATOR_H

class ColorCalculator {

public:

    static color get_color_for_pixel(const Scene &scene, double u, double v) {
        ray camera_ray = scene.get_camera_ray(u, v);
        return ray_color(camera_ray, scene.get_scene_spheres(), scene.get_background_color(), scene.get_light());
    }


private:
    static color
    ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, Light light) {
        hit_information hitInformation;

        for (const auto &sphere: spheres) {
            if (sphere.hit_by_ray(camera_ray, hitInformation)) {

                vec3 finalColor = calculate_ambient_color(light, sphere.get_material());

                if (light.hasParallelLights()) {
                    color diffuse = calculate_diffuse_component(light, hitInformation,sphere.get_material());
                    finalColor += diffuse;

                    color specular = calculate_specular_component(light, hitInformation);
                    finalColor += specular;
                }

                // Return the sum of the ambient, diffuse, and specular components.
                return finalColor;
            }
        }

        return background_color;
    }

    static color calculate_specular_component(const Light &light, const hit_information &hitInformation) {

        vec3 L = -unit_vector(light.getParallelLightDirection());

        // Calculate the direction of the view ray.
        vec3 E = -unit_vector(hitInformation.hitPoint);

        // Calculate the half vector.
        vec3 H = unit_vector(L + E);

        // Calculate the specular component.
        double KsDot = dot(H, hitInformation.normal);
        // if (KsDot < 0) KsDot;

        double Ks = pow(KsDot, 200);
        if (Ks < 0) Ks = 0;

        color paralelLightColor = light.getParallelLightColor();

        return Ks * paralelLightColor;
    }

    static color
    calculate_diffuse_component(const Light &light, const hit_information &hitInformation, const Material &material) {
        vec3 lightVector = light.getParallelLightDirection();

        // Calculate the direction of the light ray.
        vec3 L = -unit_vector(lightVector);

        // Calculate the diffuse component.
        double Kd = dot(L, hitInformation.normal);
        if (Kd < 0) Kd = 0;

        return Kd * material.getKd() * material.getColor();
    }

    static color calculate_ambient_color(const Light &light, const Material &sphere_material) {
        //Calculate the ambient color
        color ambientColor = light.getAmbientLightColor();
        // Calculate the ambient component.
        vec3 ambient = ambientColor * sphere_material.getColor() * sphere_material.getKa();
        return ambient;
    }

};


#endif
