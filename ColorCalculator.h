//
// Created by Andrei Goje on 18.05.23.
//

#ifndef COLORCALCULATOR_H
#define COLORCALCULATOR_H

#include "walls/rightWall.h"
#include "walls/behindWall.h"
#include "walls/bottomWall.h"

enum LightType {
    PARALLEL, POINT
};

class ColorCalculator {

public:

    static color get_color_for_pixel(Scene scene, double u, double v) {
        ray camera_ray = scene.get_camera_ray(u, v);

        return ray_color_2(camera_ray, scene.get_scene_spheres(), scene.get_background_color(), scene.get_light(),
                         scene.get_mesh(), scene.get_max_depth());
    }


private:
    constexpr static const double infinity = 1.79769e+308;

    static color ray_color_2(const ray& camera_ray, const std::vector<Sphere>& spheres, color background_color, const Light& light, Mesh mesh, int max_depth) {
        if (max_depth == 0) return background_color;

        hit_information hitInfo, hitInfoSquare;
        color finalColor = background_color;

        if (hit_any_sphere(camera_ray, spheres, hitInfo)) {
            finalColor = process_sphere_hit(camera_ray, spheres, light, mesh, hitInfo, max_depth, background_color);
        } else if (hit_mesh(camera_ray, mesh, hitInfoSquare)) {
            finalColor = process_mesh_hit(camera_ray, background_color, light, mesh, spheres);
        }

        return finalColor;
    }

    static bool hit_any_sphere(const ray& camera_ray, const std::vector<Sphere>& spheres, hit_information& hitInfo) {
        for (const auto& sphere : spheres) {
            if (sphere.hit_by_ray(camera_ray, hitInfo, infinity)) {
                return true;
            }
        }
        return false;
    }

    static bool hit_mesh(const ray& camera_ray, Mesh& mesh, hit_information& hitInfo) {
        return mesh.square_hit(camera_ray, hitInfo);
    }

    static color process_sphere_hit(const ray& camera_ray, const std::vector<Sphere>& spheres, const Light& light, Mesh mesh, hit_information& hitInfo, int max_depth, color background_color) {
        color reflected_color(0, 0, 0);
        const Sphere& sphere = find_sphere_which_was_hit(camera_ray, hitInfo, spheres); // Assuming this function exists and finds the hit sphere.

        ray ray_to_trace = camera_ray;
        if (sphere.get_material().getReflectance() > 0) {
            vec3 reflection_vector = reflect_dir(normalize(camera_ray.direction()), hitInfo.normal);
            ray_to_trace = ray(hitInfo.hitPoint, reflection_vector);
            reflected_color = sphere.get_material().getReflectance() * ray_color_2(ray_to_trace, spheres, background_color, light, mesh, max_depth - 1);
        }

        color finalColor = calculate_lighting_effects(sphere, hitInfo, light, ray_to_trace, spheres);
        return finalColor * (1 - sphere.get_material().getReflectance()) + reflected_color;
    }

    static color process_mesh_hit(const ray& camera_ray, const color& background_color, Light light, Mesh& mesh, const std::vector<Sphere>& spheres) {
        hit_information hitInformationSquare;

        if (mesh.square_hit(camera_ray, hitInformationSquare)) {

            color finalColor(0, 0, 0);

            finalColor += calculate_ambient_color(light, mesh.get_material());

            if (light.hasPointLights()) {
                for (int i = 0; i < 2; ++i) {

                    bool hitByShadow = shouldCastShadowOnSquare(hitInformationSquare,
                                                                light.getPointLightAtPosition(i).second,
                                                                mesh, spheres);
                    if (!hitByShadow) {
                        color diffuse = calculate_diffuse_component(light.getPointLightAtPosition(i).second,
                                                                    light.getPointLightAtPosition(i).first,
                                                                    hitInformationSquare, mesh.get_material(), POINT);
                        finalColor += diffuse;

                        color specular = calculate_specular_component(light.getPointLightAtPosition(i).second,
                                                                      light.getPointLightAtPosition(i).first,
                                                                      hitInformationSquare,
                                                                      mesh.get_material(),
                                                                      camera_ray, POINT);
                        finalColor += specular;
                    }


                }
            }

            return finalColor;
        }
        return background_color;
    }

    static color calculate_lighting_effects(const Sphere& sphere, const hit_information& hitInformation, Light light, const ray& ray_to_trace, const std::vector<Sphere>& spheres) {
        color finalColor = calculate_ambient_color(light, sphere.get_material());

        if (light.hasParallelLights()) {
            color diffuse = calculate_diffuse_component(light.getParallelLightDirection(),
                                                        light.getParallelLightColor(), hitInformation,
                                                        sphere.get_material(), PARALLEL);
            finalColor += diffuse;

            bool castShadow = shouldCastShadow(hitInformation, light.getParallelLightDirection(), spheres,
                                               sphere, PARALLEL);
            if (castShadow) {
                finalColor -= diffuse;
            } else {
                color specular = calculate_specular_component(light.getParallelLightDirection(),
                                                              light.getParallelLightColor(), hitInformation,
                                                              sphere.get_material(),
                                                              ray_to_trace, PARALLEL);
                finalColor += specular;
            }
        }

        if (light.hasPointLights()) {
            color diffuse(0, 0, 0);
            for (int i = 0; i < light.point_lights_size(); ++i) {
                diffuse += calculate_diffuse_component(light.getPointLightAtPosition(i).second,
                                                       light.getPointLightAtPosition(i).first,
                                                       hitInformation, sphere.get_material(), POINT);

                bool castShadow = shouldCastShadow(hitInformation,
                                                   light.getPointLightAtPosition(i).second,
                                                   spheres, sphere, POINT);
                if (castShadow) {
                    finalColor -= diffuse;
                } else {
                    finalColor += calculate_specular_component(light.getPointLightAtPosition(i).second,
                                                               light.getPointLightAtPosition(i).first,
                                                               hitInformation,
                                                               sphere.get_material(),
                                                               ray_to_trace, POINT);
                }

            }
            finalColor += diffuse;
        }

        return finalColor;
    }

    static const Sphere& find_sphere_which_was_hit(const ray& camera_ray, hit_information& hitInfo, const std::vector<Sphere>& spheres) {
        // Loop through all spheres to find the one that was hit by the camera ray
        for (const auto& sphere : spheres) {
            if (sphere.hit_by_ray(camera_ray, hitInfo, infinity)) {
                return sphere;
            }
        }
        throw std::runtime_error("Hit sphere not found");
    }

    static bool shouldCastShadowOnSquare(const hit_information &hitInformation, const point3 &lightPoint, Mesh &mesh,
                                         const std::vector<Sphere> &spheres) {
        point3 positionOnSquare = hitInformation.hitPoint;
        vec3 lightVector = -normalize(hitInformation.hitPoint - lightPoint);

        ray fromPointOnSquareToLight(positionOnSquare, lightVector);

        hit_information hitInformationFromPoint;
        for (Sphere sphere: spheres) {
            if (sphere.hit_by_ray(fromPointOnSquareToLight, hitInformationFromPoint,
                                  (hitInformation.hitPoint - lightPoint).length())) {
                return true;
            }
        }

        return false;
    }


    static bool shouldCastShadow(const hit_information &hitInformation, const vec3 &light,
                                 const std::vector<Sphere> &spheres, const Sphere &currentSphere,
                                 const LightType &lightType) {
        point3 positionOnSphere = hitInformation.hitPoint;
        vec3 lightVector = -normalize(light);

        if (lightType == POINT) {
            lightVector = -normalize(hitInformation.hitPoint - light);
        }

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
    calculate_specular_component(const vec3 &light, const color &lightColor, const hit_information &hitInformation,
                                 const Material &material,
                                 const ray &camera_ray, const LightType &lightType) {

        vec3 lightDir = normalize(light);
        if (lightType == POINT) {
            lightDir = normalize(hitInformation.hitPoint - light);
        }

        vec3 reflectionDir = reflect(lightDir, hitInformation.normal);
        double dotpr = dot(normalize(camera_ray.direction()), normalize(reflectionDir));
        if (dotpr < 0) dotpr = 0;

        vec3 specularTerm = lightColor * std::pow(dotpr, material.getExponent() * material.getKs());

        return specularTerm;
    }

    static color
    calculate_diffuse_component(const vec3 &light, const color &lightColor, const hit_information &hitInformation,
                                const Material &material, const LightType &lightType) {
        vec3 lightVector = light;
        if (lightType == POINT) {
            lightVector = hitInformation.hitPoint - light;
        }
        // Calculate the direction of the light ray.
        vec3 L = -normalize(lightVector);

        // Calculate the diffuse component.
        double Kd = dot(L, hitInformation.normal);
        if (Kd < 0) Kd = 0;

        return Kd * material.getKd() * material.getColor() * lightColor;
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
