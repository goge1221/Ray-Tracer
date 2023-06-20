//
// Created by Andrei Goje on 20.06.23.
//

#ifndef LAB_3_MESH_H
#define LAB_3_MESH_H

#include "../objectParser/OBJParser.h"
#include "../walls/behindWall.h"
#include "../walls/rightWall.h"
#include "../walls/bottomWall.h"
#include <memory>

class Mesh {

private:
    std::vector<vec3> vertices;
    Material material;
    behindWall bwall;
    rightWall rwall;
    bottomWall boWall;

public:

    void parse_vertices(const char *filePath) {
        OBJParser::loadOBJ(filePath, vertices);

        //behindWall behindWall(-5, 5, -2.5, 7.5, -10);
        //bottomWall bwall(-5, 5, -10, 0, -2.5);

        bwall = behindWall(-5, 5, -2.5, 7.5, -10);
        rwall = rightWall(-2.5, 7.5, -10, 0, 5);;
        boWall = bottomWall(-5, 5, -10, 0, -2.5);
    }

    bool square_hit(const ray &ray, hit_information &hit_info) {
        if (bwall.hit(ray, hit_info) || rwall.hit(ray, hit_info) || boWall.hit(ray, hit_info))
            return true;
        return false;
    }

    void set_material(Material &i_material) {
        material = i_material;
    }

    Mesh() = default;
};

#endif //LAB_3_MESH_H
