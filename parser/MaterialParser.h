//
// Created by Andrei Goje on 11.05.23.
//

#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include "../objects/material.h"

class MaterialParser {

public:

    static void get_material(XMLElement *element, Material &material) {

        XMLElement *materialElement = element->FirstChildElement("material_solid");

        if (materialElement) {
            parseColor(materialElement, material);
            parsePhongElements(materialElement, material);
            parseReflectance(materialElement, material);
            parseRefraction(materialElement, material);
            parseTransmittance(materialElement, material);
        }
    }

private:
    static void parseColor(XMLElement *materialElement, Material &material) {
        XMLElement *colorElement = materialElement->FirstChildElement("color");
        double r = 0.0, g = 0.0, b = 0.0;
        if (colorElement) {
            colorElement->QueryDoubleAttribute("r", &r);
            colorElement->QueryDoubleAttribute("g", &g);
            colorElement->QueryDoubleAttribute("b", &b);
        }
        material.setColor({r, g, b});
    }

    static void parsePhongElements(XMLElement *materialElement, Material &material) {
        double ka = 0.0, kd = 0.0, ks = 0.0;
        int exponent = 0;

        XMLElement *phongElement = materialElement->FirstChildElement("phong");
        if (phongElement) {
            phongElement->QueryAttribute("ka", &ka);
            phongElement->QueryAttribute("kd", &kd);
            phongElement->QueryAttribute("ks", &ks);
            phongElement->QueryAttribute("exponent", &exponent);
        }
        material.setPhongElement(ka, kd, ks, exponent);
    }

    static void parseReflectance(XMLElement *materialElement, Material &material) {
        XMLElement* reflectanceElement = materialElement->FirstChildElement("reflectance");
        double reflectance = 0.0;
        if (reflectanceElement) {
            reflectanceElement->QueryAttribute("r", &reflectance);
        }
        material.setReflectance(reflectance);
    }

    static void parseTransmittance(XMLElement *materialElement, Material &material) {
        XMLElement* transmittanceElement = materialElement->FirstChildElement("transmittance");
        double transmittance = 0.0;
        if (transmittanceElement) {
            transmittanceElement->QueryAttribute("t", &transmittance);
        }
        material.setTransmittance(transmittance);
    }

    static void parseRefraction(XMLElement *materialElement, Material &material) {
        XMLElement* refractionElement = materialElement->FirstChildElement("refraction");
        double iof = 0.0;
        if (refractionElement) {
            refractionElement->QueryAttribute("iof", &iof);
        }
        material.setRefraction(iof);
    }

};


#endif
