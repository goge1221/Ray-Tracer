//
// Created by Andrei Goje on 08.05.23.
//

#include <string>
#include "XMLParser.h"
#include "CameraParser.h"
#include "ObjectParser.h"
#include "LightParser.h"
/**
 * Loads an XML file containing scene information and populates a Scene object with the parsed data.
 * This method reads various components of the scene, such as background color, camera configuration,
 * spheres (scene objects), lighting, and mesh information from the XML file and uses them to construct
 * a Scene object.
 *
 * @param path The file path of the XML file to be loaded.
 * @param scene Reference to a Scene object where the parsed scene information will be stored.
 */
void XMLParser::load_xml_File(const std::string &path, Scene& scene) {

    const char *filename = path.c_str();
    document.LoadFile(filename);

    XMLElement* scene_element = document.FirstChildElement("scene");

    const char* outputFileName = scene_element->Attribute("output_file");
    outputName = outputFileName;

    color background_color = parse_background_color(scene_element);
    camera camera = parse_camera_information(scene_element);
    std::vector<Sphere> scene_spheres = parse_scene_objects(scene_element);
    Light light = parse_light_information(scene_element);

    Mesh mesh = parse_mesh_informations(path, scene_element);
    scene = Scene(background_color, camera, scene_spheres, light, mesh);
}

std::string XMLParser::get_output_name() {
    return outputName.substr(0, outputName.size()-4).append(".png");
}

/* Parse the color and set it */
color XMLParser::parse_background_color(XMLElement* scene_element) {
    XMLElement* background_element = scene_element->FirstChildElement("background_color");
    float r = 0.0, g = 0.0, b = 0.0;
    background_element->QueryFloatAttribute("r", &r);
    background_element->QueryFloatAttribute("g", &g);
    background_element->QueryFloatAttribute("b", &b);

    color background_color(r, g, b);
    return background_color;
}

/* Parse all the camera information */
camera XMLParser::parse_camera_information(XMLElement* scene_element){
    camera cam;
    (CameraParser(scene_element, cam));
    return cam;
}

Mesh XMLParser::parse_mesh_informations(const std::string& path, XMLElement *sceneElement) {
    XMLElement* surfaces_element = sceneElement->FirstChildElement("surfaces");
    if (!surfaces_element) return {};

    XMLElement* mesh_element = surfaces_element->FirstChildElement("mesh");
    if (!mesh_element) return {};

    const char* objName;
    mesh_element->QueryStringAttribute("name", &objName);

    Mesh v_mesh;
    std::string scenesPath = path.substr(0, path.size()-12);
    std::string completePath = scenesPath + std::string(objName);
    v_mesh.parse_vertices(completePath.c_str());

    Material material;
    MaterialParser::get_material(mesh_element, material);

    v_mesh.set_material(material);
    return v_mesh;
}

Light XMLParser::parse_light_information(XMLElement* sceneElement){
    return LightParser::parseLightInformations(sceneElement);
}

XMLParser::XMLParser() = default;

std::vector<Sphere> XMLParser::parse_scene_objects(XMLElement *pElement) {
    return ObjectParser::parse_all_spheres(pElement);
}


