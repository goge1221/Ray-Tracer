//
// Created by Andrei Goje on 16.05.23.
//

#ifndef LIGHT_H
#define LIGHT_H

class Light{

public:
    const color &getAmbientLightColor() const {
        return ambientLightColor;
    }

    void setAmbientLightColor(const color &lightColor) {
        Light::ambientLightColor = lightColor;
    }

    const color &getParallelLightColor() const {
        return parallelLightColor;
    }

    void setParallelLightColor(const color &lightColor) {
        Light::parallelLightColor = lightColor;
    }

    void addPointLight(color lightColor, point3 lightPosition){
        pointLightColors.push_back(lightColor);
        pointLightPositions.push_back(lightPosition);
    }

    bool hasPointLights(){
        return !(pointLightPositions.empty() && pointLightColors.empty());
    }

    std::pair<color, point3> getPointLightAtPosition(int position) const{
        return {pointLightColors.at(position), pointLightPositions.at(position)};
    }

    const vec3 &getParallelLightDirection() const {
        return parallelLightDirection;
    }

    void setParallelLightDirection(const vec3 &lightDirection) {
        Light::parallelLightDirection = lightDirection;
    }

    bool hasParallelLights(){
        vec3 undefined(0, 0, 0);
        if (parallelLightColor == undefined && parallelLightDirection == undefined){
            return false;
        }
        return true;
    }

private:
    color ambientLightColor;
    color parallelLightColor;
    vec3 parallelLightDirection;
    std::vector<color> pointLightColors;
    std::vector<point3> pointLightPositions;

};

#endif //LIGHT_H
