//
// Created by helen on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_VECTOR_H
#define TP_PERESB_HASSANH_VECTOR_H

#include <ostream>

template <unsigned int n>

class Vector {

public:
    double components[n];

public:

    Vector() = default;
    template <typename... Args>
    Vector(Args... args);
    Vector(const Vector&);

    [[maybe_unused]] static Vector zero();
    [[maybe_unused]] static Vector random_in_unit_pos_cube();

    friend std::ostream &operator<< (std::ostream &out, const Vector &v) {
        out << "(";
        for(int i = 0; i<n-1; i++) out << v.components[i] << ", ";
        out << v.components[n-1] << ")";
        return out;
    }

    std::string to_string() const {
        std::string result = "(";
        for(int i =0; i<n-1; i++)
            result += std::to_string(components[i]) + ", ";
        result += std::to_string(components[n-1]) + ")";
        return result;
    }

    double operator[](int i) const;
    double &operator[](int i);

    Vector &operator+=(const Vector&);
    Vector &operator-=(const Vector&);
    Vector operator-() const;
    Vector &operator*=(const Vector&);
    Vector &operator*=(double);
    Vector &operator/=(double);

    friend bool operator==(const Vector &a, const Vector &b) {
        for (int i=0; i<n; i++) {
            if (a.components[i] != b.components[i])
                return false;
        }
        return true;
    }
    friend bool operator!=(const Vector &a, const Vector &b) {
        return !(a==b);
    }

    [[maybe_unused]] double sq_length() const;
    [[maybe_unused]] double length() const;
    [[maybe_unused]] Vector &normalize();

    [[maybe_unused]] static double dot(const Vector&, const Vector&);

    [[maybe_unused]] static Vector cross(const Vector&, const Vector&);

    [[maybe_unused]] static Vector lerp(const Vector&, const Vector&, double x);

    [[maybe_unused]] static Vector normalized(const Vector &v);

};

template <unsigned int n>
Vector<n> operator+(const Vector<n> &a, const Vector<n> &b);

template <unsigned int n>
Vector<n> operator-(const Vector<n> &a, const Vector<n> &b);

template <unsigned int n>
Vector<n> operator*(const Vector<n> &a, const Vector<n> &b);

template <unsigned int n>
Vector<n> operator*(double a, const Vector<n> &b);

template <unsigned int n>
Vector<n> operator*(const Vector<n> &a, double b);

template <unsigned int n>
Vector<n> operator/(double a, const Vector<n> &b);

template <unsigned int n>
Vector<n> operator/(const Vector<n> &a, double b);

#include "Vector.txx"

#endif //TP_PERESB_HASSANH_VECTOR_H

