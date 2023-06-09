//
// Created by Andrei Goje on 08.05.23.
//

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

double get_color_in_range(double color) {
    if (color < 0.0) return 0.0;
    if (color > 0.999) return 0.999;
    return color;
}

void write_color_to_file(std::ofstream &out, color pixel_color) {

    out << static_cast<int>(256 * get_color_in_range(pixel_color.x())) << ' '
        << static_cast<int>(256 * get_color_in_range(pixel_color.y())) << ' '
        << static_cast<int>(256 * get_color_in_range(pixel_color.z())) << '\n';

}

#endif