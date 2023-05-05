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
Vector<n>::Vector(Args... args) : _components{static_cast<double>(args)...} {
    static_assert(sizeof...(Args) == n, "Wrong number of arguments provided");
}

template<unsigned int n>
Vector<n>::Vector(double a) {
    for (unsigned int i = 0; i < n; i++) {
        _components[i] = a;
    }
}

/// Copy constructor
template <unsigned int n>
Vector<n>::Vector(const Vector<n> &v) {
    for (int i = 0; i < n; i++) {
        this->_components[i] = v._components[i];
    }
}

// Move constructor
template <unsigned int n>
Vector<n>::Vector(Vector<n>&& other) noexcept {
    // Move the components from the other vector
    for (unsigned int i = 0; i < n; ++i) {
        _components[i] = std::move(other._components[i]);
    }
}

// Move assignment operator
template <unsigned int n>
Vector<n>& Vector<n>::operator=(Vector<n>&& other)  noexcept {
    if (this != &other) {
        // Move the components from the other vector
        for (unsigned int i = 0; i < n; ++i) {
            _components[i] = std::move(other._components[i]);
        }
    }
    return *this;
}

/**
 * @brief Copy assignment operator.
 */
template <unsigned int n>
Vector<n>& Vector<n>::operator=(const Vector<n>& other) {
    if (this != &other) {
        // Copy the components from the other vector
        for (unsigned int i = 0; i < n; ++i) {
            _components[i] = other._components[i];
        }
    }
    return *this;
}


template <unsigned int n>
[[maybe_unused]] Vector<n> Vector<n>::zero() {
    return Vector{};
}

/* OPERATORS */

template <unsigned int n>
double Vector<n>::operator[](int i) const {
    assert(i >= 0 && i < n);
    return this->_components[i];
}

template <unsigned int n>
double &Vector<n>::operator[](int i) {
    assert(i >= 0 && i < n);
    return this->_components[i];
}

template <unsigned int n>
Vector<n> &Vector<n>::operator+=(const Vector<n> &v) {
    for (int i =0; i<n; i++)
        this->_components[i] += v._components[i];
    return *this;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator-=(const Vector<n>&v) {
    for (int i =0; i<n; i++)
        this->_components[i] -= v._components[i];
    return *this;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator*=(double a) {
    for(int i = 0; i<n; i++)
        this->_components[i] *= a;
    return *this;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator/=(double a) {
    assert(a != 0.);
    return *this*=(1./a);
}

template<unsigned int n>
Vector<n> &Vector<n>::operator/=(Vector<n> v) {
    for (int i = 0; i<n; i++) {
        assert(v._components[i] != 0);
        this->_components[i] /= v._components[i];
    }
    return *this;
}

template <unsigned int n>
Vector<n> Vector<n>::operator-() const {
    Vector<n> result = Vector<n>::zero();
    for (int i=0; i<n; i++)
        result[i] = -(this->_components[i]);
    return result;
}

template <unsigned int n>
Vector<n> &Vector<n>::operator*=(const Vector<n> &v) {
    for (int i = 0; i<n; i++)
        this->_components[i] *= v._components[i];
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
        result += a._components[i] * b._components[i];
    return result;
}

template <unsigned int n>
[[maybe_unused]] Vector<n> Vector<n>::lerp(const Vector<n>&a, const Vector<n>&b, double x) {
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
        this->_components[i] /= l;
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
        result._components[i] = dist(mt);
    return result;
}

template <unsigned int n>
Vector<n> operator+(Vector<n>a, const Vector<n>&b) {
    return a += b;
}

template <unsigned int n>
Vector<n> operator-(Vector<n>a, const Vector<n>&b) {
    return a -= b;
}

template <unsigned int n>
Vector<n> operator*(Vector<n> a, const Vector<n> &b) {
    return a*=b;
}
template <unsigned int n>
Vector<n> operator*(double a, Vector<n> b) {
    return b*=a;
}
template <unsigned int n>
Vector<n> operator*(Vector<n> a, double b) {
    return a*=b;
}
template <unsigned int n>
Vector<n> operator/(double a, Vector<n> b) {
    for (int i=0; i<n; i++)
        b._components[i] = a / b._components[i];
    return b;
}

template <unsigned int n>
Vector<n> operator/(Vector<n> a, double b) {
    return a/=b;
}

template <unsigned int n>
Vector<n> operator/(Vector<n> a, const Vector<n> &b) {
    return a/=b;
}

template<unsigned int n>
Vector<n> &Vector<n>::operator%=(const Vector<n> &v) {
    for (int i = 0; i < n; ++i) {
        _components[i] = fmod(_components[i], v[i]);
        if (_components[i] < 0) {
            _components[i] += v[i];
        }
    }
}


template<unsigned int n>
Vector<n> &Vector<n>::operator%=(double b) {
    for (double &c: _components) {
        c=fmod(c, b);
        if (c < 0) {
            c += b;
        }
    }
    return *this;
}


template <unsigned int n>
Vector<n> operator%(Vector<n> a, const Vector<n> &b) {
    return Vector<n>(a)%=b;
}

template <unsigned int n>
Vector<n> operator%(Vector<n> a, double b) {
    return Vector<n>(a)%=b;
}

