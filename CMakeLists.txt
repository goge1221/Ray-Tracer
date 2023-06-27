cmake_minimum_required(VERSION 3.22)
project(Lab_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab_3 main.cpp utils/vec3.h utils/color.h utils/ray.h parser/XMLParser.cpp parser/tinyxml2.cpp parser/CameraParser.h parser/ObjectParser.h scene/Sphere.h scene/material.h parser/MaterialParser.h scene/light.h scene/hit_informations.h parser/LightParser.h scene.h ColorCalculator.h parser/OBJParser.h walls/rightWall.h walls/behindWall.h walls/bottomWall.h scene/mesh.h)
