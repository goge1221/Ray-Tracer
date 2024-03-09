//
// Created by Andrei Goje on 17.05.23.
//

#ifndef HIT_INFORMATIONS_H
#define HIT_INFORMATIONS_H

#include "../utils/ray.h"

struct hit_information{
    point3 hitPoint; // The point at which the ray intersects the object.
    vec3 normal; // The surface normal at the intersection point.

    /**
     * Sets the correct face normal based on the ray direction and the intersection surface normal.
     * This method ensures the normal is always oriented against the ray, which is necessary for
     * correct shading and light calculations.
     *
     * @param ray The incoming ray that intersects the object.
     * @param i_normal The initial normal vector at the intersection point.
     */
    void set_face_normal(const ray& ray, const vec3& i_normal) {
        // Determine if the ray is inside the object by checking the direction of the normal.
        bool inside = dot(ray.direction(), i_normal) < 0;
        // If the ray is coming from outside the object, use the normal as is.
        if (inside) normal = i_normal;
            // If the ray is inside the object, invert the normal to ensure it points against the ray.
        else normal = -i_normal;
    }
};

#endif //HIT_INFORMATIONS_H

