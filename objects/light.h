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

};

#endif //LIGHT_H
