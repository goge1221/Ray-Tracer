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

        bwall = behindWall(-5, 5, -2.5, 7.5, -10);

        initialize_walls();
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

private:

    void initialize_walls() {
        for (int i = 0; i < 3; ++i) {
            vec3 firstVertex = vertices[0 + i * 4];
            vec3 secondVertex = vertices[1 + i * 4];
            vec3 thirdVertex = vertices[2 + i * 4];
            vec3 fourthVertex = vertices[3 + i * 4];

            if (are_numbers_the_same(firstVertex.x(), secondVertex.x(), thirdVertex.x(), fourthVertex.x())) {
                //find min y and min z and add x as a position
                //this is the right wall
                double y_min = get_minimum(firstVertex.y(), secondVertex.y(), thirdVertex.y(), fourthVertex.y());
                double y_max = get_maximum(firstVertex.y(), secondVertex.y(), thirdVertex.y(), fourthVertex.y());
                double z_min = get_minimum(firstVertex.z(), secondVertex.z(), thirdVertex.z(), fourthVertex.z());
                double z_max = get_maximum(firstVertex.z(), secondVertex.z(), thirdVertex.z(), fourthVertex.z());
                double position_on_x_axis = firstVertex.x();
                rwall = rightWall(y_min, y_max, z_min, z_max, position_on_x_axis);;

            } else if (are_numbers_the_same(firstVertex.y(), secondVertex.y(), thirdVertex.y(), fourthVertex.y())) {
                //this is the bottom wall, y is the position and x and z are the positions
                double x_min = get_minimum(firstVertex.x(), secondVertex.x(), thirdVertex.x(), fourthVertex.x());
                double x_max = get_maximum(firstVertex.x(), secondVertex.x(), thirdVertex.x(), fourthVertex.x());
                double z_min = get_minimum(firstVertex.z(), secondVertex.z(), thirdVertex.z(), fourthVertex.z());
                double z_max = get_maximum(firstVertex.z(), secondVertex.z(), thirdVertex.z(), fourthVertex.z());
                double position_on_x_axis = firstVertex.y();
                boWall = bottomWall(x_min, x_max, z_min, z_max, position_on_x_axis);;

            } else {
                //this is the behind wall
                //z is the position and x and y are the things need to be parsed
                double x_min = get_minimum(firstVertex.x(), secondVertex.x(), thirdVertex.x(), fourthVertex.x());
                double x_max = get_maximum(firstVertex.x(), secondVertex.x(), thirdVertex.x(), fourthVertex.x());
                double y_min = get_minimum(firstVertex.y(), secondVertex.y(), thirdVertex.y(), fourthVertex.y());
                double y_max = get_maximum(firstVertex.y(), secondVertex.y(), thirdVertex.y(), fourthVertex.y());
                double position_on_x_axis = firstVertex.z();
                bwall = behindWall(x_min, x_max, y_min, y_max, position_on_x_axis);;

            }
        }
    }

    double get_maximum(double first, double second, double third, double fourth) {
        return std::max({first, second, third, fourth});
    }

    double get_minimum(double first, double second, double third, double fourth) {
        return std::min({first, second, third, fourth});
    }

    bool are_numbers_the_same(double first, double second, double third, double fourth) {
        return (first == second) && (second == third) && (third == fourth);
    }

};

#endif //LAB_3_MESH_H
