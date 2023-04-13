#include "Vector3.h"
#include "Vector2.h"
#include <iostream>
#include <cmath>
#include <cassert>

void test_Vector2() {
    // Test the default constructor
    Vector2 v1;
    //assert(v1.x == 0.0 && v1.y == 0.0);

    // Test the parameterized constructor
    Vector2 v2(1, 2);
    assert(v2.x == 1 && v2.y == 2);

    // Test the copy constructor
    Vector2 v3(v2);
    assert(v3.x == 1 && v3.y == 2);

    // Test the zero function
    Vector2 v4 = Vector2::zero();
    assert(v4.x == 0 && v4.y == 0);

    // Test the operator<<
    std::cout << "v2 = " << v2 << std::endl;

    // Test the operator+=
    v2 += v3;
    assert(v2.x == 2 && v2.y == 4);

    // Test the operator-=
    v2 -= v3;
    assert(v2.x == 1 && v2.y == 2);

    // Test the operator-
    Vector2 v5 = -v2;
    assert(v5.x == -1 && v5.y == -2);

    // Test the operator*=
    v2 *= v3;
    assert(v2.x == 1 && v2.y == 4);

    // Test the operator*=
    v2 *= 2;
    assert(v2.x == 2 && v2.y == 8);

    // Test the operator/=
    v2 /= 2;
    assert(v2.x == 1 && v2.y == 4);

    // Test the operator+
    Vector2 v6 = v2 + v3;
    assert(v6.x == 2 && v6.y == 6);

    // Test the operator-
    Vector2 v7 = v2 - v3;
    assert(v7.x == 0 && v7.y == 2);

    // Test the operator*
    Vector2 v8 = v2 * v3;
    assert(v8.x == 1 && v8.y == 8);

    // Test the operator* with scalar on the left
    Vector2 v9 = 2 * v3;
    assert(v9.x == 2 && v9.y == 4);

    // Test the operator* with scalar on the right
    Vector2 v10 = v3 * 2;
    assert(v10.x == 2 && v10.y == 4);

    // Test the operator/
    Vector2 v11 = v3 / 2;
    assert(v11.x == 0.5 && v11.y == 1);

    // Test the operator/ with scalar on the left
    Vector2 v12 = 2 / v3;
    assert(v12.x == 2 && v12.y == 1);

    // Test the sq_length function
    double sq_length = v3.sq_length();
    assert(sq_length == 5);

    // Test the length function
    double length = v3.length();
    assert(abs(length - sqrt(5)) < 1e-10);

    // Test the normalize function
    Vector2 v13(3, 4);
    Vector2 v14 = v13.normalize();
    assert(abs(v14.length() - 1) < 1e-10);

    // Test the dot function
    Vector2 a(2.0, 1.0);
    Vector2 b(3.0, -4.0);
    double actual_result = Vector2::dot(a, b);
    assert(actual_result == 2.0);
}

void test_Vector3() {
    // Test default constructor
    Vector3 v1{};
    assert(v1.x == 0.0);
    assert(v1.y == 0.0);
    assert(v1.z == 0.0);

    // Test constructor with parameters
    Vector3 v2(1.0, 2.0, 3.0);
    assert(v2.x == 1.0);
    assert(v2.y == 2.0);
    assert(v2.z == 3.0);

    // Test copy constructor
    Vector3 v3(v2);
    assert(v3.x == 1.0);
    assert(v3.y == 2.0);
    assert(v3.z == 3.0);

    // Test assignment operator
    v1 = v2;
    assert(v1.x == 1.0);
    assert(v1.y == 2.0);
    assert(v1.z == 3.0);

    // Test addition operator
    Vector3 v4(2.0, 3.0, 4.0);
    Vector3 v5 = v2 + v4;
    assert(v5.x == 3.0);
    assert(v5.y == 5.0);
    assert(v5.z == 7.0);

    // Test subtraction operator
    Vector3 v6 = v4 - v2;
    assert(v6.x == 1.0);
    assert(v6.y == 1.0);
    assert(v6.z == 1.0);

    // Test scalar multiplication
    Vector3 v7 = v2 * 2.0;
    assert(v7.x == 2.0);
    assert(v7.y == 4.0);
    assert(v7.z == 6.0);

    // Test scalar division
    Vector3 v8 = v2 / 2.0;
    assert(v8.x == 0.5);
    assert(v8.y == 1.0);
    assert(v8.z == 1.5);

    // Test dot product
    double dot = Vector3::dot(v2, v4);
    assert(std::abs(dot - 20.0) < 1e-6);

    // Test cross product
    Vector3 cross = Vector3::cross(v2, v4);
    assert(cross.x == -1.0);
    assert(cross.y == 2.0);
    assert(cross.z == -1.0);

    // Test magnitude
    double mag = v2.length();
    assert(std::abs(mag - std::sqrt(14.0)) < 1e-6);

    // Test normalization
    Vector3 v9 = Vector3::normalized(v2);
    assert(std::abs(v9.length() - 1.0) < 1e-6);

    // Test negation
    Vector3 v10 = -v2;
    assert(v10.x == -1.0);
    assert(v10.y == -2.0);
    assert(v10.z == -3.0);

    // Test output operator
    std::cout << v2 << std::endl;
}

int main() {

    test_Vector2();
    test_Vector3();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}