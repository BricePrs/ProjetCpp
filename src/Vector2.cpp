//
// Created by brice on 11/04/23.
//

#include "Vector2.h"


/* CONSTRUCTORS */

/// Value constructor
Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

/// Copy constructor
Vector2::Vector2(const Vector2 &v) {
    this->x = v.x;
    this->y = v.y;
}

[[maybe_unused]] Vector2 Vector2::zero() {
    return Vector2{};
}

/* OPERATORS */

std::ostream &operator<<(std::ostream &out, const Vector2& v) {
    out << "(" << v.x << ", "
        << v.y << ")";
    return out;
}


Vector2 &Vector2::operator+=(const Vector2 &v) {
    this->x += v.x,
            this->y += v.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &v) {
    return *this += v*(-1.);
}

Vector2 &Vector2::operator*=(double a) {
    this->x *= a;
    this->y *= a;
    return *this;
}

Vector2 &Vector2::operator/=(double a) {
    assert(a != 0.);
    return *this*=(1./a);
}


Vector2 Vector2::operator-() const {
    return (-1.)**this;
}

bool operator==(const Vector2 &a, const Vector2 &b) {
    return a.x == b.x &&
           a.y == b.y;
}


bool operator!=(const Vector2 &a, const Vector2 &b) {
    return !(a==b);
}


Vector2 &Vector2::operator*=(const Vector2 &v) {
    this->x*=v.x;
    this->y*=v.y;
    return *this;
}

[[maybe_unused]] double Vector2::cross(const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - b.x * a.y;
}

[[maybe_unused]] double Vector2::dot(const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

[[maybe_unused]] Vector2 Vector2::lerp(const Vector2 &a, const Vector2 &b, double x) {
    return a * (1.-x) + b * x;
}

[[maybe_unused]] double Vector2::length() const {
    return sqrt(this->sq_length());
}

[[maybe_unused]] Vector2 &Vector2::normalize() {
    double l = this->length();
    this->x /= l;
    this->y /= l;
    return *this;
}

[[maybe_unused]] Vector2 Vector2::normalized(const Vector2 &v) {
    return Vector2(v).normalize();
}

[[maybe_unused]] double Vector2::sq_length() const {
    return this->x * this->x +
           this->y * this->y;
}




Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return Vector2(a) += b;
}


Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return Vector2(a) += -b;
}


Vector2 operator*(const Vector2& a, const Vector2& b) {
    return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 operator*(double a, const Vector2& b) {
    return Vector2(b.x * a, b.y * a);
}

Vector2 operator*(const Vector2& a, double b) {
    return Vector2(a.x * b, a.y * b);
}

Vector2 operator/(double a, const Vector2& b) {
    assert(b.x != 0. && b.y != 0.);
    return Vector2(a / b.x, a / b.y);
}

Vector2 operator/(const Vector2& a, double b) {
    assert(b != 0.);
    return Vector2(a.x / b, a.y / b);
}
