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

    bool loadOBJ(const char *path, std::vector<vec3> &out_vertices, std::vector<vec3> &out_uvs,
                 std::vector<vec3> &out_normals) {

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<vec3> vertices;
        std::vector<vec3> texture_coord;
        std::vector<vec3> normals;


        std::ifstream file(path);

        if (!file) {
            std::cout << "Error while trying to read file" << std::endl;
            return false;
        }

        std::string line;

        while (std::getline(file, line)) {

            if (line[0] == '#') {
                continue;
            } else if (line.substr(0, 2) == "vt") {
                float x, y;
                std::stringstream ss(line.substr(3));
                ss >> x >> y;
                vec3 vt(x, y, 1.0);
                texture_coord.push_back(vt);
            } else if (line.substr(0, 2) == "vn") {
                float x, y, z;
                std::stringstream ss(line.substr(3));
                ss >> x >> y >> z;
                vec3 normal(x, y, z);
                normals.push_back(normal);
            } else if (line[0] == 'v') {
                float x, y, z;
                char skip;
                std::stringstream ss(line);
                ss >> skip >> x >> y >> z;
                vec3 vertex(x, y, z);
                vertices.push_back(vertex);
            } else if (line[0] == 'f') {
                int v1, t1, n1, v2, t2, n2, v3, t3, n3;
                std::sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                vertexIndices.push_back(v1);
                vertexIndices.push_back(v2);
                vertexIndices.push_back(v3);
                uvIndices.push_back(t1);
                uvIndices.push_back(t2);
                uvIndices.push_back(t3);
                normalIndices.push_back(n1);
                normalIndices.push_back(n2);
                normalIndices.push_back(n3);
            }

        }

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++) {

            // Get the indices of its attributes
            unsigned int vertexIndex = vertexIndices[i] - 1;
            unsigned int uvIndex = uvIndices[i] - 1;
            unsigned int normalIndex = normalIndices[i] - 1;

            // Get the attributes thanks to the index
            vec3 vertex = vertices[vertexIndex];
            vec3 uv = texture_coord[uvIndex];
            vec3 normal = normals[normalIndex];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_uvs.push_back(uv);
            out_normals.push_back(normal);

        }

        std::cout << "\nout_vertices: " << out_vertices.size();
        std::cout << "\nout_uvs: " << out_uvs.size();
        std::cout << "\nout_normals: " << out_normals.size();

    }

};


#endif //LAB_3_OBJPARSER_H
