//
// Created by Andrei Goje on 11.05.23.
//

#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H


#include <vector>
#include "MaterialParser.h"

class ObjectParser{

public:
    static std::vector<Sphere> parse_all_spheres(XMLElement* scene_element){

        std::vector<Sphere> spheres;
        XMLElement* surfaces_element = scene_element->FirstChildElement("surfaces");

        int sphere_id = 0;

        if (surfaces_element){
            XMLElement* sphere_element = surfaces_element->FirstChildElement("sphere");

            while (sphere_element) {

                float radius = 0.0;
                sphere_element->QueryAttribute("radius", &radius);

                XMLElement* position = sphere_element->FirstChildElement("position");

                float x = 0.0, y = 0.0, z = 0.0;
                position->QueryAttribute("x", &x);
                position->QueryAttribute("y", &y);
                position->QueryAttribute("z", &z);

                Material material;
                MaterialParser::get_material(sphere_element, material);

                //Push the new sphere to the vector we then return
                spheres.emplace_back(radius, point3(x, y, z), material, sphere_id);
                ++sphere_id;
                sphere_element = sphere_element->NextSiblingElement("sphere");  // Move to the next sphere element
            }
        }

        return spheres;

        }

    };


#endif
