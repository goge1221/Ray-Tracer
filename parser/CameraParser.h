//
// Created by Andrei Goje on 10.05.23.
//

#ifndef CAMERA_PARSER_H
#define CAMERA_PARSER_H

class CameraParser{

private:
    XMLElement* camera_element;

public:
    CameraParser(XMLElement *scene_element, camera& camera) {
        camera_element = scene_element->FirstChildElement("camera");

        point3 camera_position = get_camera_position();
        camera.set_position(camera_position);

        vec3 look_at = get_camera_lookat();
        camera.set_look_at(look_at);

        vec3 up_position = get_camera_up_position();
        camera.set_up_position(up_position);

        double camera_angle = get_camera_angle();
        camera.set_camera_angle(camera_angle);

        std::pair<double, double> resolution = get_camera_resolutions();
        camera.initialize_camera(resolution.first, resolution.second);

    }


    point3 get_camera_position(){
        float x = 0.0, y = 0.0, z = 0.0;

        XMLElement* position_element = camera_element->FirstChildElement("position");

        if (position_element) {
            position_element->QueryFloatAttribute("x", &x);
            position_element->QueryFloatAttribute("y", &y);
            position_element->QueryFloatAttribute("z", &z);
        }
        point3 camera_position(x, y, z);
        return camera_position;
    }

    vec3 get_camera_lookat(){
        float x = 0.0, y = 0.0, z = 0.0;

        XMLElement* look_at_element = camera_element->FirstChildElement("lookat");
        if (look_at_element) {
            look_at_element->QueryFloatAttribute("x", &x);
            look_at_element->QueryFloatAttribute("y", &y);
            look_at_element->QueryFloatAttribute("z", &z);
        }
        vec3 look_at(x, y, z);
        return look_at;
    }

    vec3 get_camera_up_position(){
        float x = 0.0, y = 0.0, z = 0.0;

        XMLElement* up_element = camera_element->FirstChildElement("up");
        if (up_element){
            up_element->QueryFloatAttribute("x", &x);
            up_element->QueryFloatAttribute("y", &y);
            up_element->QueryFloatAttribute("z", &z);
        }
        vec3 up_position(x, y, z);
        return up_position;
    }

    double get_camera_angle(){
        XMLElement* angle_element = camera_element->FirstChildElement("horizontal_fov");
        double camera_angle = 40;
        if (angle_element){
            angle_element->QueryAttribute("angle", &camera_angle);
        }
        return camera_angle;
    }

    std::pair<double, double> get_camera_resolutions(){
        XMLElement* resolution_element = camera_element->FirstChildElement("resolution");

        std::pair<double, double> resolution(0.0, 0.0);

        if (resolution_element){
            resolution_element->QueryAttribute("horizontal", &resolution.first);
            resolution_element->QueryAttribute("vertical", &resolution.second);
        }
        return resolution;
    }

};

#endif
