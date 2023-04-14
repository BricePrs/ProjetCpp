//
// Created by helen on 13/04/23.
//

//
// Created by helen on 13/04/23.
//

#include <random>
#include <cassert>
#include "Vector.h"
/* CONSTRUCTORS */


/// Value constructor
template <unsigned int n>
template <typename... Args>
Vector<n>::Vector(Args... args) : components{static_cast<double>(args)...} {
    static_assert(sizeof...(Args) == n, "Wrong number of arguments provided");
}

/// Copy constructor
template <unsigned int n>
Vector<n>::Vector(const Vector<n> &v) {
    for (int i = 0; i<n; i++)
        this->components[i] = v.components[i];
}
template <unsigned int n>
[[maybe_unused]] Vector<n> Vector<n>::zero() {
    return Vector{};
}

/* OPERATORS */

template <unsigned int n>
double Vector<n>::operator[](int i) const {
    assert(i >= 0 && i < n);
    return this->components[i];
}

template <unsigned int n>
double &Vector<n>::operator[](int i) {
    assert(i >= 0 && i < n);
    return this->components[i];
}

template <unsigned int n>
Vector<n> &Vector<n>::operator+=(const Vector<n> &v) {
    for (int i =0; i<n; i++)
        this->components[i] += v.components[i];
    return *this;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator-=(const Vector<n>&v) {
    return *this += v*(-1.);
}

template <unsigned int n>
Vector<n> &Vector<n>::operator*=(double a) {
    for(int i = 0; i<n; i++)
        this->components[i] *= a;
    return *this;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator/=(double a) {
    assert(a != 0.);
    return *this*=(1./a);
}

template <unsigned int n>
Vector<n> Vector<n>::operator-() const {
    return (-1.)**this;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator*=(const Vector<n>&v) {
    for (int i = 0; i<n; i++)
        this->components[i] *= v.components[i];
    return *this;
}

template <unsigned int n>
[[maybe_unused]] Vector<n> Vector<n>::cross(const Vector<n>&a, const Vector<n>&b) {
    assert(n == 3);
    return {a[1] * b[2] - b[1] * a[2],
            a[2] * b[0] - b[2] * a[0],
            a[0] * b[1] - b[0] * a[1]};
}

template <unsigned int n>
[[maybe_unused]] double Vector<n>::dot(const Vector<n>&a, const Vector<n>&b) {
    double result = 0.0;
    for (int i = 0; i<n; i++)
        result += a.components[i] * b.components[i];
    return result;
}

template <unsigned int n>
[[maybe_unused]] Vector<n> Vector<n>::lerp(const Vector<n>&a, const Vector<n>&b, double x) {
    assert(n==2);
    return a * (1.-x) + b * x;
}

template <unsigned int n>
[[maybe_unused]] double Vector<n>::length() const {
    return sqrt(this->sq_length());
}

template <unsigned int n>
[[maybe_unused]] Vector<n> &Vector<n>::normalize() {
    double l = this->length();
    for (int i=0; i<n; i++)
        this->components[i] /= l;
    return *this;
}

template <unsigned int n>
[[maybe_unused]] Vector<n> Vector<n>::normalized(const Vector<n>&v) {
    return Vector(v).normalize();
}

template <unsigned int n>
[[maybe_unused]] double Vector<n>::sq_length() const {
    return dot(*this, *this);
}

template <unsigned int n>
Vector<n> Vector<n>::random_in_unit_pos_cube() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    Vector<n> result = Vector<n>();
    for (int i = 0; i<n; i++)
        result.components[i] = dist(mt);
    return result;
}

template <unsigned int n>
Vector<n> operator+(const Vector<n>&a, const Vector<n>&b) {
    return Vector<n>(a) += b;
}

template <unsigned int n>
Vector<n> operator-(const Vector<n>&a, const Vector<n>&b) {
    return Vector<n>(a) += -b;
}

template <unsigned int n>
Vector<n> operator*(const Vector<n> &a, const Vector<n> &b) {
    return Vector<n>(a)*=b;
}
template <unsigned int n>
Vector<n> operator*(double a, const Vector<n> &b) {
    return Vector<n>(b)*=a;
}
template <unsigned int n>
Vector<n> operator*(const Vector<n> &a, double b) {
    return Vector<n>(a)*=b;
}
template <unsigned int n>
Vector<n> operator/(double a, const Vector<n> &b) {
    Vector<n> result(b);
    for (int i=0; i<n; i++)
        result.components[i] =a/b.components[i];
    return result;
}

template <unsigned int n>
Vector<n> operator/(const Vector<n> &a, double b) {
    return Vector<n>(a)/=b;
}

