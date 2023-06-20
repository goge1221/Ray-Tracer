//
// Created by Andrei Goje on 20.06.23.
//

#ifndef LAB_3_MESH_H
#define LAB_3_MESH_H

#include "../objectParser/OBJParser.h"

class Mesh{

private:
    std::vector<vec3>vertices;
    Material material;

public:
    Mesh() = default;

    void parse_vertices(const char* filePath){
        OBJParser objParser;
        objParser.loadOBJ(filePath, vertices);
    }



};

#endif //LAB_3_MESH_H
