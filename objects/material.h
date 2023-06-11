//
// Created by Andrei Goje on 11.05.23.
//

#ifndef MATERIAL_H
#define MATERIAL_H

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
