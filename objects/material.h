//
// Created by Andrei Goje on 11.05.23.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "hit_informations.h"

class Material{

private:

    color m_color;
    double ka = 0.0;
    double kd = 0.0;
    double ks = 0.0;
    int exponent = 0;
    double reflectance = 0.0;
    double transmittance = 0.0;
    double refraction = 0.0;

public:
    Material() = default;

public:
    const vec3 &getColor() const {
        return m_color;
    }

    static vec3 reflect(vec3 lightDirection, vec3 hitPointNormal) {
        return ((2.0 * dot(hitPointNormal, lightDirection)) * hitPointNormal) - lightDirection;
    }

    bool shouldScatter(const ray& in_ray, const hit_information& hit_info, color& attenuation, ray& scattered){
        vec3 reflected = reflect(normalize(in_ray.direction()), hit_info.normal);
        scattered = ray(hit_info.hitPoint, reflected);
        attenuation = m_color;
        double dotPR = dot(scattered.direction(), hit_info.normal);
        return (dotPR > 0);
    }

    double getKa() const {
        return ka;
    }

    double getKd() const {
        return kd;
    }

    double getKs() const {
        return ks;
    }

    int getExponent() const {
        return exponent;
    }

    double getReflectance() const {
        return reflectance;
    }

    double getTransmittance() const {
        return transmittance;
    }

    double getRefraction() const {
        return refraction;
    }

    void setColor(const vec3 &color) {
        m_color = color;
    }

    void setPhongElement(double ka, double kd, double ks, int exponent){
        this->ka = ka;
        this->kd = kd;
        this->ks = ks;
        this->exponent = exponent;
    }

    void setReflectance(double reflectance) {
        this->reflectance = reflectance;
    }

    void setTransmittance(double transmittance) {
        this->transmittance = transmittance;
    }

    void setRefraction(double refraction) {
        this->refraction = refraction;
    }

};


#endif
