#include <iostream>
#include <fstream>
#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/camera.h"
#include "parser/XMLParser.h"
#include "ColorCalculator.h"


void load_element_from_filepath(const std::string& path){
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
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
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

void output_black_image(){
    std::cout << "Black image\n";
}

int main() {

    std::cout << "Hello and welcome to the raytracing program of Andrei Goje 12032793\nPick an option: (Press 1 or 2 then enter)\n";
    std::cout << "1. Output a black image\n";
    std::cout << "2. Load Scene from XML File\n";

    int option;
    std::cin >> option;

    while(option != 1 && option != 2){
        std::cout << "Invalid input! Please press either 1 or 2\n";
        std::cin >> option;
    }

    if (option == 1) {
        output_black_image();
    } else if (option == 2) {
        std::cin.ignore();
        std::string filePath;
        std::cout << "Enter the path to the XML file: ";
        std::getline(std::cin, filePath);
        load_element_from_filepath(filePath);
    }


}