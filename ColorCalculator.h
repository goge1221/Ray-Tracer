//
// Created by Andrei Goje on 18.05.23.
//

#ifndef COLORCALCULATOR_H
#define COLORCALCULATOR_H

#include "walls/rightWall.h"
#include "walls/behindWall.h"
#include "walls/bottomWall.h"

class ColorCalculator {

public:

    static color get_color_for_pixel(Scene scene, double u, double v) {
        ray camera_ray = scene.get_camera_ray(u, v);
        return ray_color(camera_ray, scene.get_scene_spheres(), scene.get_background_color(), scene.get_light(), scene.get_mesh(), scene.get_max_depth());
    }


private:
    static color
    ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, Light light, Mesh mesh, int max_depth) {
        hit_information hitInformation;
        for (const auto &sphere: spheres) {
            if (sphere.hit_by_ray(camera_ray, hitInformation)) {

                color finalColor(0,0,0);
                if(max_depth < 0) return finalColor;

                finalColor = calculate_ambient_color(light, sphere.get_material());

                if (light.hasParallelLights()) {
                    color diffuse = calculate_diffuse_component(light, hitInformation, sphere.get_material());
                    finalColor += diffuse;

                    bool castShadow = shouldCastShadow(hitInformation, light, spheres, sphere);
                    if (castShadow) {
                        finalColor -= diffuse;
                    } else {
                        color specular = calculate_specular_component(light, hitInformation, sphere.get_material(),
                                                                      camera_ray);
                        finalColor += specular;
                    }
                }

                if (light.hasPointLights()) {
                    color diffuse(0, 0, 0);
                    color specular(0, 0, 0);
                    for (int i = 0; i < 2; ++i) {
                        diffuse += calculate_diffuse_component_point(light.getPointLightAtPosition(i).second,
                                                                     hitInformation, sphere.get_material());
                        specular += calculate_specular_component_point(light.getPointLightAtPosition(i).second,
                                                                       light.getPointLightAtPosition(i).first,
                                                                       hitInformation,
                                                                       sphere.get_material(),
                                                                       camera_ray);
                    }
                    finalColor += diffuse;
                    finalColor += specular;
                }
                // Return the sum of the ambient, diffuse, and specular components.
                return finalColor;
            }
        }


        if (mesh.square_hit(camera_ray, hitInformation))
            return {1, 1,1 };

        return background_color;
    }


    static bool shouldCastShadow(const hit_information &hitInformation, const Light &light,
                                 const std::vector<Sphere> &spheres, const Sphere &currentSphere) {
        point3 positionOnSphere = hitInformation.hitPoint;
        vec3 lightVector = -normalize(light.getParallelLightDirection());

        ray fromPointOnSphereToLight(positionOnSphere, lightVector);

        hit_information hitInformationFromPoint;
        for (const auto &sphere1: spheres) {
            if (sphere1 == currentSphere) continue;
            if (sphere1.hit_by_ray(fromPointOnSphereToLight, hitInformationFromPoint)) {
                return true;
            }
        }
        return false;
    }

    static vec3 reflect(vec3 lightDirection, vec3 hitPointNormal) {
        return ((2.0 * dot(hitPointNormal, lightDirection)) * hitPointNormal) - lightDirection;
    }

    static color
    calculate_specular_component(const Light &light, const hit_information &hitInformation, const Material &material,
                                 const ray &camera_ray) {

        vec3 lightDir = normalize(light.getParallelLightDirection());
        vec3 reflectionDir = reflect(lightDir, hitInformation.normal);
        double dotpr = dot(normalize(camera_ray.direction()), normalize(reflectionDir));
        if (dotpr < 0) dotpr = 0;

        vec3 specularTerm = light.getParallelLightColor() * std::pow(dotpr, material.getExponent() * material.getKs());

        return specularTerm;
    }

    static color
    calculate_specular_component_point(const point3 &lightPoint, const color &lightColor,
                                       const hit_information &hitInformation, const Material &material,
                                       const ray &camera_ray) {

        vec3 lightDir = normalize(hitInformation.hitPoint - lightPoint);
        vec3 reflectionDir = reflect(lightDir, hitInformation.normal);
        double dotpr = dot(normalize(camera_ray.direction()), normalize(reflectionDir));
        if (dotpr < 0) dotpr = 0;

        vec3 specularTerm = lightColor * std::pow(dotpr, material.getExponent() * material.getKs());

        return specularTerm;
    }


    static color
    calculate_diffuse_component_point(point3 lightPoint, const hit_information &hitInformation,
                                      const Material &material) {
        vec3 lightVector = hitInformation.hitPoint - lightPoint;

        // Calculate the direction of the light ray.
        vec3 L = -normalize(lightVector);

        // Calculate the diffuse component.
        double Kd = dot(L, hitInformation.normal);
        if (Kd < 0) Kd = 0;

        return Kd * material.getKd() * material.getColor();
    }


    static color
    calculate_diffuse_component(const Light &light, const hit_information &hitInformation, const Material &material) {
        vec3 lightVector = light.getParallelLightDirection();

        // Calculate the direction of the light ray.
        vec3 L = -normalize(lightVector);

        // Calculate the diffuse component.
        double Kd = dot(L, hitInformation.normal);
        if (Kd < 0) Kd = 0;

        return Kd * material.getKd() * material.getColor();
    }

    static color calculate_ambient_color(const Light &light, const Material &sphere_material) {
        //Get the ambient color
        color ambientColor = light.getAmbientLightColor();
        // Calculate the ambient component.
        vec3 ambient = ambientColor * sphere_material.getColor() * sphere_material.getKa();
        return ambient;
    }

};


#endif
