//
// Created by Andrei Goje on 08.05.23.
//

#include <iostream>
#include <string>
#include "XMLParser.h"
#include "CameraParser.h"
#include "ObjectParser.h"

void XMLParser::load_xml_File(const std::string &scenename) {
    std::string basepath = "/Users/andreigoje/Desktop/Uni local/GFX/Lab3/scenes/";
    std::string fullpath = basepath + scenename;

    const char *filename = fullpath.c_str();
    document.LoadFile(filename);

    XMLElement* scene_element = document.FirstChildElement("scene");

    parse_background_color(scene_element);
    parse_camera_informations(scene_element);
    parser_surface_informations(scene_element);

}

/* Parse the color and set it */
void XMLParser::parse_background_color(XMLElement* scene_element) {
    XMLElement* background_element = scene_element->FirstChildElement("background_color");
    float r = 0.0, g = 0.0, b = 0.0;
    background_element->QueryFloatAttribute("r", &r);
    background_element->QueryFloatAttribute("g", &g);
    background_element->QueryFloatAttribute("b", &b);

    color received_color(r, g, b);
    set_background_color(received_color);
}

void XMLParser::set_background_color(color& color) {
    background_color = color;
}

/* Parse all the camera information */
void XMLParser::parse_camera_informations(XMLElement* scene_element){
    (CameraParser(scene_element, camera));
}

camera XMLParser::get_camera() {
    return camera;
}

color XMLParser::get_background_color() {
    return background_color;
}

void XMLParser::parser_surface_informations(XMLElement *pElement) {
    ObjectParser objectParser;
    scene_spheres = objectParser.parse_all_spheres(pElement);
}

std::vector<Sphere> XMLParser::get_scene_spheres() {
    return scene_spheres;
}

XMLParser::XMLParser() = default;

