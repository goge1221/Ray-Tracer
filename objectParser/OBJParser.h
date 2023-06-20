//
// Created by Andrei Goje on 12.06.23.
//

#ifndef LAB_3_OBJPARSER_H
#define LAB_3_OBJPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <string>
#include "../headers/vec3.h"

using namespace std;

class OBJParser {
public:
    OBJParser() = default;

    static bool loadOBJ(const char *path, std::vector<vec3> &vertices) {

        std::ifstream file(path);

        if (!file) {
            std::cout << "Error while trying to read file" << std::endl;
            return false;
        }

        std::string line;

        while (std::getline(file, line)) {

            if (line[0] == '#') continue;
            else if (line[0] == 'v' && line[1] == ' ') {
                double x, y, z;
                char skipChar;
                std::stringstream ss(line);
                ss >> skipChar >> x >> y >> z;
                vec3 vertex(x, y, z);
                vertices.push_back(vertex);
            }
        }
        return true;
    }

};


#endif //LAB_3_OBJPARSER_H
