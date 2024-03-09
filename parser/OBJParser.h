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

using namespace std;
/**
 * @class OBJLoader
 * @brief Class for loading 3D models from OBJ files.
 *
 * This class provides functionalities to load vertex data from OBJ format files.
 * It only processes vertices positions marked with 'v' in the file.
 */
class OBJParser {
public:
    OBJParser() = default;
    /**
     * Loads vertex data from an OBJ file.
     *
     * This static method opens the specified OBJ file, reads its vertex data (positions),
     * and stores them in the provided vector. It ignores all other types of data in the file.
     *
     * @param path The path to the OBJ file.
     * @param vertices A reference to a vector of vec3 where vertex positions will be stored.
     * @return true if the file is successfully loaded and processed, false otherwise.
     */
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
