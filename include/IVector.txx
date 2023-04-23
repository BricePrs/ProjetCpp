//
// Created by helen on 13/04/23.
//

//
// Created by helen on 13/04/23.
//

#include <random>
#include <cassert>
#include "IVector.h"
/* CONSTRUCTORS */


/// Value constructor
template <unsigned int n>
template <typename... Args>
IVector<n>::IVector(Args... args) : components{static_cast<int32_t>(args)...} {
    static_assert(sizeof...(Args) == n, "Wrong number of arguments provided");
}

template<unsigned int n>
IVector<n>::IVector(int32_t a) {
    for (unsigned int i = 0; i < n; i++) {
        components[i] = a;
    }
}

/// Copy constructor
template <unsigned int n>
IVector<n>::IVector(const IVector<n> &v) {
    for (int i = 0; i < n; i++) {
        this->components[i] = v.components[i];
    }
}

template <unsigned int n>
[[maybe_unused]] IVector<n> IVector<n>::zero() {
    return IVector{};
}

/* OPERATORS */

template <unsigned int n>
int32_t IVector<n>::operator[](int i) const {
    assert(i >= 0 && i < n);
    return this->components[i];
}

template <unsigned int n>
int32_t &IVector<n>::operator[](int i) {
    assert(i >= 0 && i < n);
    return this->components[i];
}

template <unsigned int n>
IVector<n> &IVector<n>::operator+=(const IVector<n> &v) {
    for (int i =0; i<n; i++)
        this->components[i] += v.components[i];
    return *this;
}

template <unsigned int n>
IVector<n> &IVector<n>::operator-=(const IVector<n>&v) {
    return *this += v*(-1.);
}

template <unsigned int n>
IVector<n> &IVector<n>::operator*=(int32_t a) {
    for(int i = 0; i<n; i++)
        this->components[i] *= a;
    return *this;
}

template <unsigned int n>
IVector<n> &IVector<n>::operator/=(int32_t a) {
    assert(a != 0.);
    return *this*=(1./a);
}


template<unsigned int n>
IVector<n> &IVector<n>::operator%=(int32_t a) {
    assert(a != 0.);
    for(int i = 0; i<n; i++)
        this->components[i] %= a;
}

template<unsigned int n>
IVector &IVector<n>::operator%=(const IVector &b) {
    for(int i = 0; i<n; i++)
        this->components[i] %= b[i];
}

template <unsigned int n>
IVector<n> IVector<n>::operator-() const {
    return (-1.)**this;
}

template <unsigned int n>
IVector<n> &IVector<n>::operator*=(const IVector<n>&v) {
    for (int i = 0; i<n; i++)
        this->components[i] *= v.components[i];
    return *this;
}

template <unsigned int n>
[[maybe_unused]] IVector<n> IVector<n>::cross(const IVector<n>&a, const IVector<n>&b) {
    assert(n == 3);
    return {a[1] * b[2] - b[1] * a[2],
            a[2] * b[0] - b[2] * a[0],
            a[0] * b[1] - b[0] * a[1]};
}

template <unsigned int n>
[[maybe_unused]] int32_t IVector<n>::dot(const IVector<n>&a, const IVector<n>&b) {
    int32_t result = 0.0;
    for (int i = 0; i<n; i++)
        result += a.components[i] * b.components[i];
    return result;
}

template <unsigned int n>
[[maybe_unused]] IVector<n> IVector<n>::lerp(const IVector<n>&a, const IVector<n>&b, int32_t x) {
    return a * (1.-x) + b * x;
}

template <unsigned int n>
[[maybe_unused]] int32_t IVector<n>::length() const {
    return sqrt(this->sq_length());
}

template <unsigned int n>
[[maybe_unused]] IVector<n> &IVector<n>::normalize() {
    int32_t l = this->length();
    for (int i=0; i<n; i++)
        this->components[i] /= l;
    return *this;
}

template <unsigned int n>
[[maybe_unused]] IVector<n> IVector<n>::normalized(const IVector<n>&v) {
    return IVector(v).normalize();
}

template <unsigned int n>
[[maybe_unused]] int32_t IVector<n>::sq_length() const {
    return dot(*this, *this);
}

template <unsigned int n>
IVector<n> operator+(const IVector<n>&a, const IVector<n>&b) {
    return IVector<n>(a) += b;
}

template <unsigned int n>
IVector<n> operator-(const IVector<n>&a, const IVector<n>&b) {
    return IVector<n>(a) += -b;
}

template <unsigned int n>
IVector<n> operator*(const IVector<n> &a, const IVector<n> &b) {
    return IVector<n>(a)*=b;
}
template <unsigned int n>
IVector<n> operator*(int32_t a, const IVector<n> &b) {
    return IVector<n>(b)*=a;
}
template <unsigned int n>
IVector<n> operator*(const IVector<n> &a, int32_t b) {
    return IVector<n>(a)*=b;
}
template <unsigned int n>
IVector<n> operator/(int32_t a, const IVector<n> &b) {
    IVector<n> result(b);
    for (int i=0; i<n; i++)
        result.components[i] =a/b.components[i];
    return result;
}

template <unsigned int n>
IVector<n> operator/(const IVector<n> &a, int32_t b) {
    return IVector<n>(a)/=b;
}

template <unsigned int n>
IVector<n> operator%(const IVector<n> &a, const IVector<n> &b) {
    return IVector<n>(a)%=b;
}

template <unsigned int n>
IVector<n> operator%(const IVector<n> &a, int32_t b) {
    return IVector<n>(a)%=b;
}
