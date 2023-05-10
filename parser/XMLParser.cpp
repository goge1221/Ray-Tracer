//
// Created by Andrei Goje on 08.05.23.
//

#include <iostream>
#include <string>
#include "XMLParser.h"


void XMLParser::load_xml_File(const std::string &scenename) {
    std::string basepath = "/Users/andreigoje/Desktop/Uni local/GFX/Lab3/scenes/";
    std::string fullpath = basepath + scenename;

    const char *filename = fullpath.c_str();
    document.LoadFile(filename);

    XMLElement* scene_element = document.FirstChildElement("scene");

    parse_background_color(scene_element);
    parse_camera_informations(scene_element);

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
    XMLElement* camera_element = scene_element->FirstChildElement("camera");

    float x = 0.0, y = 0.0, z = 0.0;

    XMLElement* position_element = camera_element->FirstChildElement("position");
    if (position_element) {
        position_element->QueryFloatAttribute("x", &x);
        position_element->QueryFloatAttribute("y", &y);
        position_element->QueryFloatAttribute("z", &z);
    }
    vec3 camera_position(x, y, z);
    camera.set_position(camera_position);

    XMLElement* look_at_element = camera_element->FirstChildElement("lookat");
    if (look_at_element) {
        look_at_element->QueryFloatAttribute("x", &x);
        look_at_element->QueryFloatAttribute("y", &y);
        look_at_element->QueryFloatAttribute("z", &z);
    }
    vec3 look_at(x, y, z);
    camera.set_look_at(look_at);

    XMLElement* up_element = camera_element->FirstChildElement("up");
    if (up_element){
        up_element->QueryFloatAttribute("x", &x);
        up_element->QueryFloatAttribute("y", &y);
        up_element->QueryFloatAttribute("z", &z);
    }
    vec3 up_position(x, y, z);
    camera.set_up_position(up_position);

    XMLElement* angle_element = camera_element->FirstChildElement("horizontal_fov");
    double camera_angle = 4;
    if (angle_element){
        angle_element->QueryAttribute("angle", &camera_angle);
    }
    camera.set_camera_angle(camera_angle);

    XMLElement* resolution_element = camera_element->FirstChildElement("resolution");
    double horizontal = 0, vertical = 0;
    if (resolution_element){
        resolution_element->QueryAttribute("horizontal", &horizontal);
        resolution_element->QueryAttribute("vertical", &vertical);
    }
    camera.initialize_camera(horizontal, vertical);

}

camera XMLParser::get_camera() {
    return camera;
}

XMLParser::XMLParser() = default;

