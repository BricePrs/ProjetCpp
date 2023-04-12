//
// Created by brice on 11/04/23.
//

#include "Vecteur2.h"


/* CONSTRUCTORS */

/// Value constructor
Vecteur2::Vecteur2(double x, double y) {
    this->x = x;
    this->y = y;
}

/// Copy constructor
Vecteur2::Vecteur2(const Vecteur2 &v) {
    this->x = v.x;
    this->y = v.y;
}

[[maybe_unused]] Vecteur2 Vecteur2::zero() {
    return Vecteur2{};
}

/* OPERATORS */

std::ostream &operator<<(std::ostream &out, const Vecteur2& v) {
    out << "(" << v.x << ", "
        << v.y << ")";
    return out;
}


Vecteur2 & Vecteur2::operator+=(const Vecteur2 &v) {
    this->x += v.x,
            this->y += v.y;
    return *this;
}

Vecteur2 &Vecteur2::operator-=(const Vecteur2 &v) {
    return *this += v*(-1.);
}

Vecteur2 &Vecteur2::operator*=(double a) {
    this->x *= a;
    this->y *= a;
    return *this;
}

Vecteur2 &Vecteur2::operator/=(double a) {
    assert(a != 0.);
    return *this*=(1./a);
}


Vecteur2 Vecteur2::operator-() const {
    return (-1.)**this;
}

bool operator==(const Vecteur2 &a, const Vecteur2 &b) {
    return a.x == b.x &&
           a.y == b.y;
}


bool operator!=(const Vecteur2 &a, const Vecteur2 &b) {
    return !(a==b);
}


Vecteur2 &Vecteur2::operator*=(const Vecteur2 &v) {
    this->x*=v.x;
    this->y*=v.y;
    return *this;
}

[[maybe_unused]] double Vecteur2::cross(const Vecteur2 &a, const Vecteur2 &b) {
    return a.x * b.y - b.x * a.y;
}

[[maybe_unused]] double Vecteur2::dot(const Vecteur2 &a, const Vecteur2 &b) {
    return a.x * b.x + a.y * b.y;
}

[[maybe_unused]] Vecteur2 Vecteur2::lerp(const Vecteur2 &a, const Vecteur2 &b, double x) {
    return a * (1.-x) + b * x;
}

[[maybe_unused]] double Vecteur2::length() const {
    return sqrt(this->sq_length());
}

[[maybe_unused]] Vecteur2 &Vecteur2::normalize() {
    double l = this->length();
    this->x /= l;
    this->y /= l;
    return *this;
}

[[maybe_unused]] Vecteur2 Vecteur2::normalized(const Vecteur2 &v) {
    return Vecteur2(v).normalize();
}

[[maybe_unused]] double Vecteur2::sq_length() const {
    return this->x * this->x +
           this->y * this->y;
}




Vecteur2 operator+(const Vecteur2 &a, const Vecteur2 &b) {
    return Vecteur2(a) += b;
}


Vecteur2 operator-(const Vecteur2 &a, const Vecteur2 &b) {
    return Vecteur2(a) += -b;
}


Vecteur2 operator*(const Vecteur2& a, const Vecteur2& b) {
    return Vecteur2(a.x * b.x, a.y * b.y);
}

Vecteur2 operator*(double a, const Vecteur2& b) {
    return Vecteur2(b.x * a, b.y * a);
}

Vecteur2 operator*(const Vecteur2& a, double b) {
    return Vecteur2(a.x * b, a.y * b);
}

Vecteur2 operator/(double a, const Vecteur2& b) {
    assert(b.x != 0. && b.y != 0.);
    return Vecteur2(a / b.x, a / b.y);
}

Vecteur2 operator/(const Vecteur2& a, double b) {
    assert(b != 0.);
    return Vecteur2(a.x / b, a.y / b);
}
