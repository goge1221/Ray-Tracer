cmake_minimum_required(VERSION 3.22)
project(Lab_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab_3 main.cpp headers/vec3.h headers/color.h headers/ray.h parser/XMLParser.cpp parser/tinyxml2.cpp parser/CameraParser.h parser/ObjectParser.h objects/Sphere.h)
