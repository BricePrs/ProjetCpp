//
// Created by helen on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_VECTOR_H
#define TP_PERESB_HASSANH_VECTOR_H

#include <ostream>

template <unsigned int n>
class Vector {
public:
    /**
     * @brief Components of the vector.
     */
    double _components[n];

    /**
     * @brief Default constructor.
     */
    Vector() = default;

    /**
     * @brief Constructor that initializes all components with the same value.
     * @param a The value to initialize the components with.
     */
    Vector(double a);

    /**
     * @brief Move constructor for Vector class.
     * @param other The other Vector object to move from.
     */
    Vector<n>(Vector<n>&& other) noexcept ;

    /**
     * @brief Move assignment operator for Vector class.
     * @param other The other Vector object to move from.
     * @return A reference to the current Vector object.
     */
    Vector<n>& operator=(Vector<n>&& other) noexcept;

    /**
    * @brief Copy assignment operator for Vector class.
    * @param other The other Vector object to copy from.
    * @return A reference to the current Vector object.
    */
    Vector<n>& operator=(const Vector<n>& other);

    /**
     * @brief Variadic constructor that initializes the components with the given values.
     * @tparam Args The types of the arguments.
     * @param args The values to initialize the components with.
     */
    template <typename... Args>
    Vector(Args... args);

    /**
     * @brief Copy constructor.
     * @param other The vector to copy from.
     */
    Vector(const Vector& v);

    /**
     * @brief Returns a zero vector.
     * @return A zero vector.
     */
    [[maybe_unused]] static Vector zero();

    /**
     * @brief Returns a random vector in the unit positive cube.
     * @return A random vector in the unit positive cube.
     */
    [[maybe_unused]] static Vector random_in_unit_pos_cube();

    /**
     * @brief Overloaded output stream operator for printing the vector.
     * @param out The output stream.
     * @param v The vector to print.
     * @return The output stream.
     */
    friend std::ostream &operator<< (std::ostream &out, const Vector &v) {
        out << "(";
        for(int i = 0; i<n-1; i++) out << v._components[i] << ", ";
        out << v._components[n - 1] << ")";
        return out;
    }

    /**
     * @brief Returns a string representation of the vector.
     * @return A string representation of the vector.
     */
    std::string to_string() const {
        std::string result = "(";
        for(int i =0; i<n-1; i++)
            result += std::to_string(_components[i]) + ", ";
        result += std::to_string(_components[n - 1]) + ")";
        return result;
    }
    /**
     * @brief Returns the value of the i-th component of the vector.
     * @param i The index of the component to retrieve.
     * @return The value of the i-th component.
     */
    double operator[](int i) const;

    /**
     * @brief Returns a reference to the i-th component of the vector.
     * @param i The index of the component to retrieve.
     * @return A reference to the i-th component.
     */
    double &operator[](int i);

    /**
     * @brief Adds another vector to this vector.
     * @param other The vector to add.
     * @return A reference to this vector.
     */
    Vector &operator+=(const Vector& other);

    /**
     * @brief Subtracts another vector from this vector.
     * @param other The vector to subtract.
     * @return A reference to this vector.
     */
    Vector &operator-=(const Vector& other);

    /**
     * @brief Negates this vector.
     * @return The negated vector.
     */
    Vector operator-() const;

    /**
     * @brief Multiplies this vector with another vector component-wise.
     * @param other The vector to multiply with.
     * @return A reference to this vector.
     */
    Vector &operator*=(const Vector& other);

    /**
     * @brief Multiplies this vector with a scalar.
     * @param scalar The scalar to multiply with.
     * @return A reference to this vector.
     */
    Vector &operator*=(double scalar);

    /**
     * @brief Divides this vector by a scalar.
     * @param scalar The scalar to divide by.
     * @return A reference to this vector.
     */
    Vector &operator/=(double scalar);

    /**
     * @brief Divides each component of this vector by each component of v.
     * @param scalar v the divisor
     * @return A reference to this vector.
     */
    Vector &operator/=(Vector<n> v);

    /**
 * @brief Apply modulo v[i] to each component i of this vector
 * @param scalar v the divisor
 * @return A reference to this vector.
 */
    Vector &operator%=(const Vector<n> &v);

    /**
 * @brief Apply modulo v to each component of this vector
 * @param scalar v
 * @return A reference to this vector.
 */
    Vector &operator%=(double v);

    /**
     * @brief operator== Compares two vectors for equality.
     * @param a The first vector.
     * @param b The second vector.
     * @return `true` if the vectors are equal, `false` otherwise.
     */
    friend bool operator==(const Vector &a, const Vector &b) {
        for (int i=0; i<n; i++) {
            if (a._components[i] != b._components[i])
                return false;
        }
        return true;
    }

    /**
     * @brief operator!= Compares two vectors for inequality.
     * @param a The first vector.
     * @param b The second vector.
     * @return `true` if the vectors are not equal, `false` otherwise.
     */
    friend bool operator!=(const Vector &a, const Vector &b) {
        return !(a==b);
    }

    /**
     * @brief sq_length Returns the square of the length of the vector.
     * @return The square of the length of the vector.
     */
    [[maybe_unused]] double sq_length() const;

    /**
     * @brief length Returns the length of the vector.
     * @return The length of the vector.
     */
    [[maybe_unused]] double length() const;

    /**
     * @brief normalize Normalizes the vector.
     * @return A reference to the normalized vector.
     */
    [[maybe_unused]] Vector &normalize();

    /**
     * @brief dot Computes the dot product of two vectors.
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @return The dot product of the two vectors.
     */
    [[maybe_unused]] static double dot(const Vector &v1, const Vector &v2);

    /**
     * @brief cross Computes the cross product of two vectors.
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @return The cross product of the two vectors.
     */
    [[maybe_unused]] static Vector cross(const Vector &v1, const Vector &v2);

    /**
     * @brief lerp Performs a linear interpolation between two vectors.
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param x The interpolation factor (should be between 0 and 1).
     * @return The interpolated vector.
     */
    [[maybe_unused]] static Vector lerp(const Vector &v1, const Vector &v2, double x);

    /**
     * @brief normalized Returns a normalized copy of the vector.
     * @param v The vector to normalize.
     * @return The normalized copy of the vector.
     */
    [[maybe_unused]] static Vector normalized(const Vector &v);
};


/**
 * @brief Adds two vectors component-wise.
 * @tparam n The number of components in the vectors.
 * @param a The first vector to add.
 * @param b The second vector to add.
 * @return The vector resulting from adding the two input vectors component-wise.
 */
template <unsigned int n>
Vector<n> operator+(Vector<n> a, const Vector<n> &b);

/**
 * @brief Subtracts two vectors component-wise.
 * @tparam n The number of components in the vectors.
 * @param a The vector to subtract from.
 * @param b The vector to subtract.
 * @return The vector resulting from subtracting the second vector from the first component-wise.
 */
template <unsigned int n>
Vector<n> operator-(Vector<n> a, const Vector<n> &b);

/**
 * @brief Multiplies two vectors component-wise.
 * @tparam n The number of components in the vectors.
 * @param a The first vector to multiply.
 * @param b The second vector to multiply.
 * @return The vector resulting from multiplying the two input vectors component-wise.
 */
template <unsigned int n>
Vector<n> operator*(Vector<n> a, const Vector<n> &b);

/**
 * @brief Multiplies a vector by a scalar.
 * @tparam n The number of components in the vector.
 * @param a The scalar to multiply the vector by.
 * @param b The vector to multiply.
 * @return The vector resulting from multiplying the input vector by the scalar.
 */
template <unsigned int n>
Vector<n> operator*(double a, Vector<n> b);

/**
 * @brief Multiplies a vector by a scalar.
 * @tparam n The number of components in the vector.
 * @param a The vector to multiply.
 * @param b The scalar to multiply the vector by.
 * @return The vector resulting from multiplying the input vector by the scalar.
 */
template <unsigned int n>
Vector<n> operator*(Vector<n> a, double b);

/**
 * @brief Divides a vector by a scalar.
 * @tparam n The number of components in the vector.
 * @param a The vector to divide.
 * @param b The scalar to divide the vector by.
 * @return The vector resulting from dividing the input vector by the scalar.
 */
template <unsigned int n>
Vector<n> operator/(Vector<n> a, double b);



/**
 * @brief Apply modulo b[i] to each component a[i] of this vector
 * @tparam n The number of components in the vector.
 * @param a The vector to divide.
 * @param b The modulo.
 * @return The vector resulting from the modulo.
 */
template <unsigned int n>
Vector<n> operator%(Vector<n> a, const Vector<n> &b);

/**
 * @brief Apply modulo b to each component a[i] of this vector
 * @tparam n The number of components in the vector.
 * @param a The vector to divide.
 * @param b The scalar
 * @return The vector resulting from the modulo.
 */
template <unsigned int n>
Vector<n> operator%(Vector<n> a, double b);


/**
 * @brief Divides a vector by a scalar.
 * @tparam n The number of components in the vector.
 * @param a The vector to divide.
 * @param b The scalar to divide the vector by.
 * @return The vector resulting from dividing the input vector by the scalar.
 */
template <unsigned int n>
Vector<n> operator/(Vector<n> a, const Vector<n> &b);

#include "Vector.txx"

#endif //TP_PERESB_HASSANH_VECTOR_H

