//
// Created by Andrei Goje on 09.05.23.
//

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <vector>
#include "tinyxml2.h"
#include "../headers/camera.h"
#include "../objects/Sphere.h"
#include "../objects/light.h"

using namespace tinyxml2;

class XMLParser{

private:
    XMLDocument document;
    color background_color;
    camera camera;
    std::vector<Sphere> scene_spheres;
    Light light;

    void set_background_color(color&);
    void parse_background_color(XMLElement *scene_element);
    void parse_camera_informations(XMLElement *scene_element);

public:
    XMLParser();
    void load_xml_File(const std::string&);
    class camera get_camera();
    color get_background_color();
    std::vector<Sphere> get_scene_spheres();
    void parser_surface_informations(XMLElement *pElement);
    void parse_light_information(XMLElement *sceneElement);

    Light get_light_informations();
};


#endif
