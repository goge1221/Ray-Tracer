//
// Created by Andrei Goje on 18.05.23.
//

#ifndef COLORCALCULATOR_H
#define COLORCALCULATOR_H

#include "walls/rightWall.h"
#include "walls/behindWall.h"
#include "walls/bottomWall.h"

enum LightType{
    PARALLEL, POINT
};

class ColorCalculator {

public:

    static color get_color_for_pixel(Scene scene, double u, double v) {
        ray camera_ray = scene.get_camera_ray(u, v);
        return ray_color(camera_ray, scene.get_scene_spheres(), scene.get_background_color(), scene.get_light(),
                         scene.get_mesh(), scene.get_max_depth());
    }


private:
    constexpr static const double infinity = 1.79769e+308;

    static color
    ray_color(const ray &camera_ray, const std::vector<Sphere> &spheres, color background_color, Light light, Mesh mesh,
              int max_depth) {
        hit_information hitInformation;

        if (max_depth == 0) return background_color;

        for (const auto &sphere: spheres) {
            if (sphere.hit_by_ray(camera_ray, hitInformation, infinity)) {

                color reflected_color(0, 0, 0);

                ray ray_to_trace = camera_ray;

                if (sphere.get_material().getReflectance() > 0) {
                    vec3 reflection_vector = reflect_dir(normalize(camera_ray.direction()), hitInformation.normal);
                    ray_to_trace = ray(hitInformation.hitPoint, reflection_vector);
                    reflected_color = sphere.get_material().getReflectance() *
                                      ray_color(ray_to_trace, spheres, background_color, light, mesh, max_depth - 1);
                }


                color finalColor = calculate_ambient_color(light, sphere.get_material());

                if (light.hasParallelLights()) {
                    color diffuse = calculate_diffuse_component(light, hitInformation, sphere.get_material());
                    finalColor += diffuse;

                    bool castShadow = shouldCastShadow(hitInformation, light, spheres, sphere);
                    if (castShadow) {
                        finalColor -= diffuse;
                    } else {
                        color specular = calculate_specular_component(light, hitInformation, sphere.get_material(),
                                                                      ray_to_trace);
                        finalColor += specular;
                    }
                }

                if (light.hasPointLights()) {
                    color diffuse(0, 0, 0);
                    for (int i = 0; i < 2; ++i) {
                        diffuse += calculate_diffuse_component_point(light.getPointLightAtPosition(i).second,
                                                                     light.getPointLightAtPosition(i).first,
                                                                     hitInformation, sphere.get_material());

                        bool castShadow = shouldCastShadowWithPointLight(hitInformation,
                                                                         light.getPointLightAtPosition(i).second,
                                                                         spheres, sphere);
                        if (castShadow) {
                            finalColor -= diffuse;
                        } else {
                            finalColor += calculate_specular_component_point(light.getPointLightAtPosition(i).second,
                                                                             light.getPointLightAtPosition(i).first,
                                                                             hitInformation,
                                                                             sphere.get_material(),
                                                                             ray_to_trace);
                        }

                    }
                    finalColor += diffuse;
                }

                // Return the sum of the ambient, diffuse, and specular components.
                return finalColor * (1 - sphere.get_material().getReflectance()) + reflected_color;
            }
        }
        hit_information hitInformationSquare;

        if (mesh.square_hit(camera_ray, hitInformationSquare)) {

            color finalColor(0, 0, 0);

            finalColor += calculate_ambient_color(light, mesh.get_material());

            if (light.hasPointLights()) {
                for (int i = 0; i < 2; ++i) {

                    bool hitByShadow = shouldCastShadowOnSquare(hitInformationSquare, light.getPointLightAtPosition(i).second,
                                                                mesh, spheres);
                    if (!hitByShadow) {
                        color diffuse = calculate_diffuse_component_point(light.getPointLightAtPosition(i).second,
                                                                          light.getPointLightAtPosition(i).first,
                                                                          hitInformationSquare, mesh.get_material());
                        finalColor += diffuse;

                        color specular = calculate_specular_component_point(light.getPointLightAtPosition(i).second,
                                                                            light.getPointLightAtPosition(i).first,
                                                                            hitInformationSquare,
                                                                            mesh.get_material(),
                                                                            camera_ray);
                        finalColor += specular;
                    }

                }
            }

            return finalColor;
        }

        return background_color;
    }


    static bool shouldCastShadowWithPointLight(const hit_information &hitInformation, const point3 &lightPoint,
                                               const std::vector<Sphere> &spheres, const Sphere &currentSphere) {
        point3 positionOnSphere = hitInformation.hitPoint;
        vec3 lightVector = -normalize(hitInformation.hitPoint - lightPoint);

        ray fromPointOnSphereToLight(positionOnSphere, lightVector);

        hit_information hitInformationFromPoint;
        for (const auto &sphere1: spheres) {
            if (sphere1 == currentSphere) continue;
            if (sphere1.hit_by_ray(fromPointOnSphereToLight, hitInformationFromPoint, infinity)) {
                return true;
            }
        }
        return false;
    }

    static bool shouldCastShadowOnSquare(const hit_information &hitInformation, const point3 &lightPoint, Mesh &mesh,
                                         const std::vector<Sphere>& spheres) {
        point3 positionOnSquare = hitInformation.hitPoint;
        vec3 lightVector = -normalize(hitInformation.hitPoint - lightPoint);

        ray fromPointOnSquareToLight(positionOnSquare, lightVector);

        hit_information hitInformationFromPoint;
        for (Sphere sphere: spheres) {
            if (sphere.hit_by_ray(fromPointOnSquareToLight, hitInformationFromPoint, (hitInformation.hitPoint - lightPoint).length())) {
                    return true;
            }
        }

        return false;
    }


    static bool shouldCastShadow(const hit_information &hitInformation, const Light &light,
                                 const std::vector<Sphere> &spheres, const Sphere &currentSphere) {
        point3 positionOnSphere = hitInformation.hitPoint;
        vec3 lightVector = -normalize(light.getParallelLightDirection());

        ray fromPointOnSphereToLight(positionOnSphere, lightVector);

        hit_information hitInformationFromPoint;
        for (const auto &sphere1: spheres) {
            if (sphere1 == currentSphere) continue;
            if (sphere1.hit_by_ray(fromPointOnSphereToLight, hitInformationFromPoint, infinity)) {
                return true;
            }
        }
        return false;
    }

    static vec3 reflect(vec3 lightDirection, vec3 hitPointNormal) {
        return ((2.0 * dot(hitPointNormal, lightDirection)) * hitPointNormal) - lightDirection;
    }

    static vec3 reflect_dir(vec3 lightDirection, vec3 hitPointNormal) {
        return ((2.0 * dot(-lightDirection, hitPointNormal)) * hitPointNormal) + lightDirection;
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
    calculate_diffuse_component_point(point3 lightPoint, color lightColor, const hit_information &hitInformation,
                                      const Material &material) {
        vec3 lightVector = -normalize(hitInformation.hitPoint - lightPoint);

        // Calculate the diffuse component.
        double Kd = dot(lightVector, hitInformation.normal);
        if (Kd < 0) Kd = 0;

        return Kd * material.getKd() * material.getColor() * lightColor;
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
