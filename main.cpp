#include <iostream>
#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/camera.h"
#include "parser/XMLParser.h"
#include "ColorCalculator.h"

int main() {

    Scene scene;
    XMLParser xmlParser;
    xmlParser.load_xml_File("example2.xml", scene);

    int image_width = scene.get_image_width();
    int image_height = scene.get_image_height();

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            color pixel_color = ColorCalculator::get_color_for_pixel(scene, u, v);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}


