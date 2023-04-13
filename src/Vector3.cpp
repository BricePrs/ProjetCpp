//
// Created by brice on 11/04/23.
//

#include <random>
#include "Vector3.h"


/* CONSTRUCTORS */

/// Value constructor
Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/// Copy constructor
Vector3::Vector3(const Vector3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

[[maybe_unused]] Vector3 Vector3::zero() {
    return Vector3{};
}

/* OPERATORS */

std::ostream &operator<<(std::ostream &out, const Vector3& v) {
    out << "(" << v.x << ", "
        << v.y << ", "
        << v.z << ")";
    return out;
}


Vector3 & Vector3::operator+=(const Vector3 &v) {
    this->x += v.x,
    this->y += v.y,
    this->z += v.z;
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &v) {
    return *this += v*(-1.);
}

Vector3 &Vector3::operator*=(double a) {
    this->x *= a;
    this->y *= a;
    this->z *= a;
    return *this;
}

Vector3 &Vector3::operator/=(double a) {
    assert(a != 0.);
    return *this*=(1./a);
}


Vector3 Vector3::operator-() const {
    return (-1.)**this;
}

bool operator==(const Vector3 &a, const Vector3 &b) {
    return a.x == b.x &&
           a.y == b.y &&
           a.z == b.z;
}


bool operator!=(const Vector3 &a, const Vector3 &b) {
    return !(a==b);
}


Vector3 &Vector3::operator*=(const Vector3 &v) {
    this->x*=v.x;
    this->y*=v.y;
    this->z*=v.z;
    return *this;
}

[[maybe_unused]] Vector3 Vector3::cross(const Vector3 &a, const Vector3 &b) {
    return {a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y};
}

[[maybe_unused]] double Vector3::dot(const Vector3 &a, const Vector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[maybe_unused]] Vector3 Vector3::lerp(const Vector3 &a, const Vector3 &b, double x) {
    return a * (1.-x) + b * x;
}

[[maybe_unused]] double Vector3::length() const {
    return sqrt(this->sq_length());
}

[[maybe_unused]] Vector3 &Vector3::normalize() {
    double l = this->length();
    this->x /= l;
    this->y /= l;
    this->z /= l;
    return *this;
}

[[maybe_unused]] Vector3 Vector3::normalized(const Vector3 &v) {
    return Vector3(v).normalize();
}

[[maybe_unused]] double Vector3::sq_length() const {
    return this->x * this->x +
           this->y * this->y +
           this->z * this->z;
}

Vector3 Vector3::random_in_unit_pos_cube() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return{
        dist(mt),
        dist(mt),
        dist(mt)
    };
}


Vector3 operator+(const Vector3 &a, const Vector3 &b) {
    return Vector3(a) += b;
}


Vector3 operator-(const Vector3 &a, const Vector3 &b) {
    return Vector3(a) += -b;
}

Vector3 operator*(const Vector3& a, const Vector3& b) {
    return Vector3(a)*=b;
}

Vector3 operator*(double a, const Vector3& b) {
    return Vector3(b)*=a;
}

Vector3 operator*(const Vector3& a, double b) {
    return Vector3(a)*=b;
}

Vector3 operator/(double a, const Vector3& b) {
    return Vector3(b)/=a;
}

Vector3 operator/(const Vector3& a, double b) {
    return Vector3(a)/=b;
}
