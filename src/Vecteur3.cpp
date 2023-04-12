//
// Created by brice on 11/04/23.
//

#include "Vecteur3.h"


/* CONSTRUCTORS */

/// Value constructor
Vecteur3::Vecteur3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/// Copy constructor
Vecteur3::Vecteur3(const Vecteur3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

[[maybe_unused]] Vecteur3 Vecteur3::zero() {
    return Vecteur3{};
}

/* OPERATORS */

std::ostream &operator<<(std::ostream &out, const Vecteur3& v) {
    out << "(" << v.x << ", "
        << v.y << ", "
        << v.z << ")";
    return out;
}


Vecteur3 & Vecteur3::operator+=(const Vecteur3 &v) {
    this->x += v.x,
    this->y += v.y,
    this->z += v.z;
    return *this;
}

Vecteur3 &Vecteur3::operator-=(const Vecteur3 &v) {
    return *this += v*(-1.);
}

Vecteur3 &Vecteur3::operator*=(double a) {
    this->x *= a;
    this->y *= a;
    this->z *= a;
    return *this;
}

Vecteur3 &Vecteur3::operator/=(double a) {
    assert(a != 0.);
    return *this*=(1./a);
}


Vecteur3 Vecteur3::operator-() const {
    return (-1.)**this;
}

bool operator==(const Vecteur3 &a, const Vecteur3 &b) {
    return a.x == b.x &&
           a.y == b.y &&
           a.z == b.z;
}


bool operator!=(const Vecteur3 &a, const Vecteur3 &b) {
    return !(a==b);
}


Vecteur3 &Vecteur3::operator*=(const Vecteur3 &v) {
    this->x*=v.x;
    this->y*=v.y;
    this->z*=v.z;
    return *this;
}

[[maybe_unused]] Vecteur3 Vecteur3::cross(const Vecteur3 &a, const Vecteur3 &b) {
    return {a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y};
}

[[maybe_unused]] double Vecteur3::dot(const Vecteur3 &a, const Vecteur3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[maybe_unused]] Vecteur3 Vecteur3::lerp(const Vecteur3 &a, const Vecteur3 &b, double x) {
    return a * (1.-x) + b * x;
}

[[maybe_unused]] double Vecteur3::length() const {
    return sqrt(this->sq_length());
}

[[maybe_unused]] Vecteur3 &Vecteur3::normalize() {
    double l = this->length();
    this->x /= l;
    this->y /= l;
    this->z /= l;
    return *this;
}

[[maybe_unused]] Vecteur3 Vecteur3::normalized(const Vecteur3 &v) {
    return Vecteur3(v).normalize();
}

[[maybe_unused]] double Vecteur3::sq_length() const {
    return this->x * this->x +
           this->y * this->y +
           this->z * this->z;
}




Vecteur3 operator+(const Vecteur3 &a, const Vecteur3 &b) {
    return Vecteur3(a) += b;
}


Vecteur3 operator-(const Vecteur3 &a, const Vecteur3 &b) {
    return Vecteur3(a) += -b;
}

Vecteur3 operator*(const Vecteur3& a, const Vecteur3& b) {
    return Vecteur3(a)*=b;
}

Vecteur3 operator*(double a, const Vecteur3& b) {
    return Vecteur3(b)*=a;
}

Vecteur3 operator*(const Vecteur3& a, double b) {
    return Vecteur3(a)*=b;
}

Vecteur3 operator/(double a, const Vecteur3& b) {
    return Vecteur3(b)/=a;
}

Vecteur3 operator/(const Vecteur3& a, double b) {
    return Vecteur3(a)/=b;
}
