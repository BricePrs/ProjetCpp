//
// Created by brice on 09/03/23.
//

#ifndef LAB3_INFRA_VECTEUR3_H
#define LAB3_INFRA_VECTEUR3_H

#include <cassert>
#include <cmath>
#include <ostream>

class Vecteur3 {

public:
    double x;
    double y;
    double z;

public:

    Vecteur3() = default;
    Vecteur3(double x, double y, double z);
    Vecteur3(const Vecteur3&);

    [[maybe_unused]] [[maybe_unused]] static Vecteur3 zero();

    friend std::ostream &operator<<(std::ostream &out, const Vecteur3& v);

    Vecteur3 &operator+=(const Vecteur3&);
    Vecteur3 &operator-=(const Vecteur3&);
    Vecteur3 operator-() const;
    Vecteur3 &operator*=(const Vecteur3&);
    Vecteur3 &operator*=(double);
    Vecteur3 &operator/=(double);

    friend bool operator==(const Vecteur3 &a, const Vecteur3 &b);
    friend bool operator!=(const Vecteur3 &a, const Vecteur3 &b);

    [[maybe_unused]] double sq_length() const;
    [[maybe_unused]] double length() const;
    [[maybe_unused]] Vecteur3 &normalize();

    [[maybe_unused]] static double dot(const Vecteur3&, const Vecteur3&);

    [[maybe_unused]] static Vecteur3 cross(const Vecteur3&, const Vecteur3&);

    [[maybe_unused]] static Vecteur3 lerp(const Vecteur3&, const Vecteur3&, double x);

    [[maybe_unused]] static Vecteur3 normalized(const Vecteur3 &v);

};

Vecteur3 operator+(const Vecteur3 &a, const Vecteur3 &b);

Vecteur3 operator-(const Vecteur3 &a, const Vecteur3 &b);

Vecteur3 operator*(const Vecteur3& a, const Vecteur3& b);
Vecteur3 operator*(double a, const Vecteur3& b);
Vecteur3 operator*(const Vecteur3& a, double b);

Vecteur3 operator/(double a, const Vecteur3& b);
Vecteur3 operator/(const Vecteur3& a, double b);

#endif //LAB3_INFRA_VECTEUR3_H
