//
// Created by brice on 09/03/23.
//

#ifndef LAB3_INFRA_Vector2_H
#define LAB3_INFRA_Vector2_H

#include <cassert>
#include <cmath>
#include <ostream>

class Vector2 {

public:
    double x;
    double y;

public:

    Vector2() = default;
    Vector2(double x, double y);
    Vector2(const Vector2&);

    [[maybe_unused]] static Vector2 zero();

    friend std::ostream &operator<<(std::ostream &out, const Vector2& v);
    std::string to_string() const {
        return std::to_string(x) + ", " + std::to_string(y);
    }

    Vector2 &operator+=(const Vector2&);
    Vector2 &operator-=(const Vector2&);
    Vector2 operator-() const;
    Vector2 &operator*=(const Vector2&);
    Vector2 &operator*=(double);
    Vector2 &operator/=(double);

    friend bool operator==(const Vector2 &a, const Vector2 &b);
    friend bool operator!=(const Vector2 &a, const Vector2 &b);

    [[maybe_unused]] double sq_length() const;
    [[maybe_unused]] double length() const;
    [[maybe_unused]] Vector2 &normalize();

    [[maybe_unused]] static double dot(const Vector2&, const Vector2&);

    [[maybe_unused]] static double cross(const Vector2&, const Vector2&);

    [[maybe_unused]] static Vector2 lerp(const Vector2&, const Vector2&, double x);

    [[maybe_unused]] static Vector2 normalized(const Vector2 &v);

};

Vector2 operator+(const Vector2 &a, const Vector2 &b);

Vector2 operator-(const Vector2 &a, const Vector2 &b);

Vector2 operator*(const Vector2& a, const Vector2& b);
Vector2 operator*(double a, const Vector2& b);
Vector2 operator*(const Vector2& a, double b);

Vector2 operator/(double a, const Vector2& b);
Vector2 operator/(const Vector2& a, double b);

#endif //LAB3_INFRA_Vector2_H
