#include <iostream>
#include "OBJParser.h"

int main() {

    OBJParser objParser;

    std::vector<vec3>vec;
    objParser.loadOBJ("/Users/andreigoje/Desktop/Uni local/GFX/Lab3/scenes/example4.xml", vec, vec, vec);
    return 0;
}
