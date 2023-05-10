//
// Created by Andrei Goje on 08.05.23.
//

#include <iostream>
#include <string>
#include "XMLParser.h"


void XMLParser::load_xml_File(const std::string &scenename) {
    std::string basepath = "/Users/andreigoje/Desktop/Uni local/GFX/Lab_3/scenes/";
    std::string fullpath = basepath + scenename;
    const char *filename = fullpath.c_str();
    document.LoadFile(filename);

    XMLElement* scene_element = document.FirstChildElement("scene");

    parse_background_color(scene_element);

    std::cout << background_color;
}

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

XMLParser::XMLParser() = default;

