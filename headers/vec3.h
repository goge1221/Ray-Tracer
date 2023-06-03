//
// Created by Andrei Goje on 08.05.23.
//

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
    // Constructors
    vec3() : coord{0, 0, 0} {}
    vec3(double x, double y, double z) : coord{x, y, z} {}


    vec3 operator-() const { return {-x(), -y(), -z()}; }

    double operator[](int i) const { return coord[i]; }
    double &operator[](int i) { return coord[i]; }

    vec3 &operator+=(const vec3 &other) {
        for (int i = 0; i < 3; ++i) {
            coord[i] += other[i];
        }
        return *this;
    }

    vec3 &operator*=(const double t) {
        for (double & i : coord) i *= t;
        return *this;
    }

    vec3 &operator-=(const vec3 &other) {
        for (int i = 0; i < 3; ++i) {
            coord[i] -= other[i];
        }
        return *this;
    }

    vec3 &operator/=(const double t) {
        return *this *= 1 / t;
    }

    bool operator==(const vec3 &other) const {
        for (int i = 0; i < 3; ++i) {
            if (coord[i] != other[i])
                return false;
        }
        return true;
    }

    double length() const {
        return sqrt(x() * x() + y() * y() + z() * z());
    }

    //Getters
    double x() const { return coord[0]; }
    double y() const { return coord[1]; }
    double z() const { return coord[2]; }

private:
    double coord[3];
};

// Type aliases for vec3
using point3 = vec3;
using color = vec3;

inline vec3 operator+(const vec3 &l_vec, const vec3 &r_vec) {
    return {l_vec.x() + r_vec.x(), l_vec.y() + r_vec.y(), l_vec.z() + r_vec.z()};
}

inline vec3 operator-(const vec3 &l_vec, const vec3 &r_vec) {
    return {l_vec.x() - r_vec.x(), l_vec.y() - r_vec.y(), l_vec.z() - r_vec.z()};
}

inline vec3 operator*(const vec3 &l_vec, const vec3 &r_vec) {
    return {l_vec.x() * r_vec.x(), l_vec.y() * r_vec.y(), l_vec.z() * r_vec.z()};
}

inline vec3 operator*(double scalar, const vec3 &vec) {
    return {scalar * vec.x(), scalar * vec.y(), scalar * vec.z()};
}

inline vec3 operator*(const vec3 &vec, double scalar) {
    return scalar * vec;
}

inline vec3 operator/(vec3 vec, double t) {
    return (1 / t) * vec;
}

inline double dot(const vec3 &l_vec, const vec3 &r_vec) {
    return l_vec.x() * r_vec.x() + l_vec.y() * r_vec.y() + l_vec.z() * r_vec.z();
}

inline vec3 cross(const vec3 &l_vec, const vec3 &r_vec) {
    return {l_vec.y() * r_vec.z() - l_vec.z() * r_vec.y(),
            l_vec.z() * r_vec.x() - l_vec.x() * r_vec.z(),
            l_vec.x() * r_vec.y() - l_vec.y() * r_vec.x()};
}

inline vec3 normalize(vec3 vec) {
    return vec / vec.length();
}

#endif
