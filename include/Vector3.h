//
// Created by brice on 09/03/23.
//

#ifndef LAB3_INFRA_Vector3_H
#define LAB3_INFRA_Vector3_H

#include <cassert>
#include <cmath>
#include <ostream>

class Vector3 {

public:
    double x;
    double y;
    double z;

public:

    Vector3() = default;
    Vector3(double x, double y, double z);
    Vector3(const Vector3&);

    [[maybe_unused]] static Vector3 zero();
    [[maybe_unused]] static Vector3 random_in_unit_pos_cube();

    friend std::ostream &operator<<(std::ostream &out, const Vector3& v);
    std::string to_string() const {
        return std::to_string(x) + ", " + std::to_string(y) + + ", " + std::to_string(z);
    }

    Vector3 &operator+=(const Vector3&);
    Vector3 &operator-=(const Vector3&);
    Vector3 operator-() const;
    Vector3 &operator*=(const Vector3&);
    Vector3 &operator*=(double);
    Vector3 &operator/=(double);

    friend bool operator==(const Vector3 &a, const Vector3 &b);
    friend bool operator!=(const Vector3 &a, const Vector3 &b);

    [[maybe_unused]] double sq_length() const;
    [[maybe_unused]] double length() const;
    [[maybe_unused]] Vector3 &normalize();

    [[maybe_unused]] static double dot(const Vector3&, const Vector3&);

    [[maybe_unused]] static Vector3 cross(const Vector3&, const Vector3&);

    [[maybe_unused]] static Vector3 lerp(const Vector3&, const Vector3&, double x);

    [[maybe_unused]] static Vector3 normalized(const Vector3 &v);

};

Vector3 operator+(const Vector3 &a, const Vector3 &b);

Vector3 operator-(const Vector3 &a, const Vector3 &b);

Vector3 operator*(const Vector3& a, const Vector3& b);
Vector3 operator*(double a, const Vector3& b);
Vector3 operator*(const Vector3& a, double b);

Vector3 operator/(double a, const Vector3& b);
Vector3 operator/(const Vector3& a, double b);

#endif //LAB3_INFRA_Vector3_H
