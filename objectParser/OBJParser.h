//
// Created by Andrei Goje on 12.06.23.
//

#ifndef LAB_3_OBJPARSER_H
#define LAB_3_OBJPARSER_H

//
// Created by parallels on 6/14/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "../headers/vec3.h"

using namespace std;

class OBJParser {
public:
    OBJParser() = default;

    bool loadOBJ(const char * path, std::vector<vec3> & out_vertices, std::vector<vec3> & out_uvs, std::vector<vec3> & out_normals){

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<vec3> temp_vertices;
        std::vector<vec3> temp_uvs;
        std::vector<vec3> temp_normals;


        std::ifstream file(path);

        if (!file){
            std::cout << "Error while trying to read file" << std::endl;
            return false;
        }

        std::string line;

        while(std::getline(file, line)){

            if (line[0] == '#'){
                std::cout << "skipped   ";
            }
            else if(line[0] == 'v'){
                float x, y, z;
                char skip;
                std::stringstream ss(line);
                ss >> skip >> x >> y >> z;
                vec3 vertex(x, y, z);
                temp_vertices.push_back(vertex);
            }
        }

    }

};



#endif //LAB_3_OBJPARSER_H
