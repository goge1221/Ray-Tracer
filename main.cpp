#include <iostream>
#include <fstream>
#include "utils/color.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "scene/camera.h"
#include "parser/XMLParser.h"
#include "ColorCalculator.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"


void load_element_from_filepath(const std::string &path) {
    Scene scene;
    XMLParser xmlParser;
    xmlParser.load_xml_File(path, scene);

    int image_width = scene.get_image_width();
    int image_height = scene.get_image_height();
    std::string outputName = xmlParser.get_output_name(); // Ensure the output name ends with .png

    // Prepare a buffer for pixel data (RGB)
    std::vector<unsigned char> pixels(image_width * image_height * 3);

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            color pixel_color = ColorCalculator::get_color_for_pixel(scene, u, v);

            // Flip the y-axis by subtracting j from the total height
            int flipped_j = image_height - 1 - j;
            int index = (flipped_j * image_width + i) * 3;
            pixels[index] = static_cast<unsigned char>(255 * get_color_in_range(pixel_color.x()));
            pixels[index + 1] = static_cast<unsigned char>(255 * get_color_in_range(pixel_color.y()));
            pixels[index + 2] = static_cast<unsigned char>(255 * get_color_in_range(pixel_color.z()));
        }
    }

    // Write the PNG file
    stbi_write_png(outputName.c_str(), image_width, image_height, 3, pixels.data(), image_width * 3);

    std::cerr << "\nDone.\n";
}


int main() {

    std::cout << "Hello and welcome to the raytracing program of Andrei Goje 12032793\n";
    std::cout << "Enter the path to the XML file: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    load_element_from_filepath(filePath);
    std::cout << filePath.substr(filePath.find_last_of('/') + 1, filePath.size() - 4);
    std::cout << " outputted into the directory cmake-build-debug directory as a PPM file.\n";

}