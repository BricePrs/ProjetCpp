//
// Created by brice on 09/03/23.
//

#ifndef LAB3_INFRA_VECTEUR2_H
#define LAB3_INFRA_VECTEUR2_H

#include <cassert>
#include <cmath>
#include <ostream>

class Vecteur2 {

public:
    double x;
    double y;

public:

    Vecteur2() = default;
    Vecteur2(double x, double y);
    Vecteur2(const Vecteur2&);

    [[maybe_unused]] static Vecteur2 zero();

    friend std::ostream &operator<<(std::ostream &out, const Vecteur2& v);

    Vecteur2 &operator+=(const Vecteur2&);
    Vecteur2 &operator-=(const Vecteur2&);
    Vecteur2 operator-() const;
    Vecteur2 &operator*=(const Vecteur2&);
    Vecteur2 &operator*=(double);
    Vecteur2 &operator/=(double);

    friend bool operator==(const Vecteur2 &a, const Vecteur2 &b);
    friend bool operator!=(const Vecteur2 &a, const Vecteur2 &b);

    [[maybe_unused]] double sq_length() const;
    [[maybe_unused]] double length() const;
    [[maybe_unused]] Vecteur2 &normalize();

    [[maybe_unused]] static double dot(const Vecteur2&, const Vecteur2&);

    [[maybe_unused]] static double cross(const Vecteur2&, const Vecteur2&);

    [[maybe_unused]] static Vecteur2 lerp(const Vecteur2&, const Vecteur2&, double x);

    [[maybe_unused]] static Vecteur2 normalized(const Vecteur2 &v);

};

Vecteur2 operator+(const Vecteur2 &a, const Vecteur2 &b);

Vecteur2 operator-(const Vecteur2 &a, const Vecteur2 &b);

Vecteur2 operator*(const Vecteur2& a, const Vecteur2& b);
Vecteur2 operator*(double a, const Vecteur2& b);
Vecteur2 operator*(const Vecteur2& a, double b);

Vecteur2 operator/(double a, const Vecteur2& b);
Vecteur2 operator/(const Vecteur2& a, double b);

#endif //LAB3_INFRA_VECTEUR2_H
