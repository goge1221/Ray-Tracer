//
// Created by Andrei Goje on 18.05.23.
//

#ifndef COLORCALCULATOR_H
#define COLORCALCULATOR_H

class ColorCalculator{

public:

    static color get_color_for_pixel(const Scene& scene, double u, double v) {
        ray camera_ray = scene.get_camera_ray(u, v);
        return ray_color(camera_ray, scene.get_scene_spheres(), scene.get_background_color(), scene.get_light());
    }


private:
    static color ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, Light light) {
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

};


#endif
