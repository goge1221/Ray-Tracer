#include <iostream>
#include <fstream>
#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/camera.h"
#include "parser/XMLParser.h"
#include "ColorCalculator.h"
#include "objectParser/OBJParser.h"



void load_element_from_filepath(const std::string &path) {
    Scene scene;
    XMLParser xmlParser;
    xmlParser.load_xml_File(path, scene);

    int image_width = scene.get_image_width();
    int image_height = scene.get_image_height();

    std::string outputName = xmlParser.get_output_name();
    std::ofstream ppmFile(outputName);

    // Render
    ppmFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            color pixel_color = ColorCalculator::get_color_for_pixel(scene, u, v);
            write_color_to_file(ppmFile, pixel_color);
        }
    }
    ppmFile.close();
    std::cerr << "\nDone.\n";
}


int main() {

    load_element_from_filepath("/Users/andreigoje/Desktop/Uni local/GFX/Lab3/scenes/example4.xml");



/*    std::cout << "Hello and welcome to the raytracing program of Andrei Goje 12032793\n";
    std::cout << "Enter the path to the XML file: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    load_element_from_filepath(filePath);
    std::cout << filePath.substr(filePath.find_last_of('/') + 1, filePath.size() - 4);
    std::cout << " outputted into the directory cmake-build-debug directory as a PPM file.\n"; */

}