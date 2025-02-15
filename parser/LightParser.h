//
// Created by Andrei Goje on 18.05.23.
//

#ifndef LIGHTPARSER_H
#define LIGHTPARSER_H
/**
 * @class LightParser
 * @brief Responsible for parsing light related data from XML.
 *
 * This class is designed to interpret and extract light related settings or configurations
 * stored in an XML format. It parses different kinds of light, Point lights, Parallel light and Ambient lights
 * with their corresponding color.
 */
class LightParser {

public:

    static Light parseLightInformations(XMLElement *scene_element) {
        Light light;

        auto light_element = scene_element->FirstChildElement("lights");

        light.setAmbientLightColor(getAmbientLightColor(light_element));
        light.setParallelLightColor(getParallelLightColor(light_element));
        light.setParallelLightDirection(getParallelLightDirection(light_element));
        parsePointLight(light_element, light);

        return light;
    }

private:

    static void parsePointLight(XMLElement *lights_element, Light &light) {
        auto point_light = lights_element->FirstChildElement("point_light");

        while(point_light) {
            auto color_element = point_light->FirstChildElement("color");
            if (!color_element) continue;

            double r, g, b;
            color_element->QueryAttribute("r", &r);
            color_element->QueryAttribute("g", &g);
            color_element->QueryAttribute("b", &b);

            auto position_element = point_light->FirstChildElement("position");
            if (!position_element) continue;
            double x, y, z;
            position_element->QueryAttribute("x", &x);
            position_element->QueryAttribute("y", &y);
            position_element->QueryAttribute("z", &z);

            light.addPointLight(color(r,g,b), point3(x,y,z));

            point_light = point_light->NextSiblingElement("point_light");
        }
    }

    static color getParallelLightDirection(XMLElement *lights_element) {
        auto ambient_element = lights_element->FirstChildElement("parallel_light");

        double x = 0.0, y = 0.0, z = 0.0;

        if (ambient_element) {
            auto direction_element = ambient_element->FirstChildElement("direction");
            if (direction_element) {
                direction_element->QueryAttribute("x", &x);
                direction_element->QueryAttribute("y", &y);
                direction_element->QueryAttribute("z", &z);
            }
        }
        vec3 lightDirection(x, y, z);
        return lightDirection;
    }

    static color getParallelLightColor(XMLElement *lights_element) {
        auto ambient_element = lights_element->FirstChildElement("parallel_light");

        double r = 0.0, g = 0.0, b = 0.0;

        if (ambient_element) {
            auto color_element = ambient_element->FirstChildElement("color");
            color_element->QueryAttribute("r", &r);
            color_element->QueryAttribute("g", &g);
            color_element->QueryAttribute("b", &b);
        }
        color parallelColor(r, g, b);
        return parallelColor;
    }


    static color getAmbientLightColor(XMLElement *lights_element) {
        auto ambient_element = lights_element->
                FirstChildElement("ambient_light")->FirstChildElement("color");

        double r = 0.0, g = 0.0, b = 0.0;

        if (ambient_element) {
            ambient_element->QueryAttribute("r", &r);
            ambient_element->QueryAttribute("g", &g);
            ambient_element->QueryAttribute("b", &b);
        }
        color ambient_color(r, g, b);
        return ambient_color;
    }

};

#endif
