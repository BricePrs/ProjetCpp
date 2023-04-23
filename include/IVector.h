//
// Created by helen on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_VECTOR_H
#define TP_PERESB_HASSANH_VECTOR_H

#include <ostream>

template <unsigned int n>

class IVector {

public:
    int32_t components[n];

public:

    IVector() = default;
    IVector(int32_t a);

    template <typename... Args>
    IVector(Args... args);
    IVector(const IVector&);

    [[maybe_unused]] static IVector zero();

    friend std::ostream &operator<< (std::ostream &out, const IVector &v) {
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

    int32_t operator[](int i) const;
    int32_t &operator[](int i);

    IVector &operator+=(const IVector&);
    IVector &operator-=(const IVector&);
    IVector operator-() const;
    IVector &operator*=(const IVector&);
    IVector &operator*=(int32_t);
    IVector &operator/=(int32_t);
    IVector &operator%=(int32_t);
    IVector &operator%=(const IVector&);

    friend bool operator==(const IVector &a, const IVector &b) {
        for (int i=0; i<n; i++) {
            if (a.components[i] != b.components[i])
                return false;
        }
        return true;
    }
    friend bool operator!=(const IVector &a, const IVector &b) {
        return !(a==b);
    }

    [[maybe_unused]] int32_t sq_length() const;
    [[maybe_unused]] int32_t length() const;
    [[maybe_unused]] IVector &normalize();

    [[maybe_unused]] static int32_t dot(const IVector&, const IVector&);

    [[maybe_unused]] static IVector cross(const IVector&, const IVector&);

    [[maybe_unused]] static IVector lerp(const IVector&, const IVector&, int32_t x);

    [[maybe_unused]] static IVector normalized(const IVector &v);

};

template <unsigned int n>
IVector<n> operator+(const IVector<n> &a, const IVector<n> &b);

template <unsigned int n>
IVector<n> operator-(const IVector<n> &a, const IVector<n> &b);

template <unsigned int n>
IVector<n> operator*(const IVector<n> &a, const IVector<n> &b);

template <unsigned int n>
IVector<n> operator*(int32_t a, const IVector<n> &b);

template <unsigned int n>
IVector<n> operator*(const IVector<n> &a, int32_t b);

template <unsigned int n>
IVector<n> operator/(int32_t a, const IVector<n> &b);

template <unsigned int n>
IVector<n> operator/(const IVector<n> &a, int32_t b);

template <unsigned int n>
IVector<n> operator%(const IVector<n> &a, const IVector<n> &b);

template <unsigned int n>
IVector<n> operator%(const IVector<n> &a, int32_t b);

#include "IVector.txx"

#endif //TP_PERESB_HASSANH_VECTOR_H

