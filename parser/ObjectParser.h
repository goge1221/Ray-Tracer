//
// Created by Andrei Goje on 11.05.23.
//

#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H


#include <vector>
#include "../objects/Sphere.h"

class ObjectParser{


public:
    std::vector<Sphere> parse_all_spheres(XMLElement* scene_element){

        std::vector<Sphere> spheres;
        XMLElement* surfaces_element = scene_element->FirstChildElement("surfaces");

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

                //Push the new sphere to the vector we then return
                spheres.emplace_back(radius, point3(x, y, z));

                sphere_element = sphere_element->NextSiblingElement("sphere");  // Move to the next sphere element
            }
        }

        return spheres;

        }

    };


#endif
