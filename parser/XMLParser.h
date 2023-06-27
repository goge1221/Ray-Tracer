//
// Created by Andrei Goje on 09.05.23.
//

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "tinyxml2.h"
#include "../scene.h"

using namespace tinyxml2;

class XMLParser{

private:
    XMLDocument document;
    std::string outputName;
    color parse_background_color(XMLElement *scene_element);
    camera parse_camera_information(XMLElement *scene_element);
    std::vector<Sphere> parse_scene_objects(XMLElement *pElement);
    Light parse_light_information(XMLElement *sceneElement);
    Mesh parse_mesh_informations(const std::string& path, XMLElement *sceneElement);

public:
    XMLParser();
    void load_xml_File(const std::string&, Scene& scene);
    std::string get_output_name();
};


#endif
