#include <iostream>
#include <cmath>
#include <cassert>
#include "Vector.h"

void test_Vector2() {
    // Test the default constructor
    Vector<2> v1;
    //assert(v1[0] == 0.0 && v1[1] == 0.0);

    // Test the parameterized constructor
    Vector<2> v2(1.0, 2.0);
    assert(v2[0] == 1 && v2[1] == 2);

    // Test the copy constructor
    Vector<2> v3(v2);
    assert(v3[0] == 1 && v3[1] == 2);

    // Test the zero function
    Vector<2> v4 = Vector<2>::zero();
    assert(v4[0] == 0 && v4[1] == 0);

    // Test the operator<<
    std::cout << "v2 = " << v2 << std::endl;

    // Test the operator+=
    v2 += v3;
    assert(v2[0] == 2 && v2[1] == 4);

    // Test the operator-=
    v2 -= v3;
    assert(v2[0] == 1 && v2[1] == 2);

    // Test the operator-
    Vector<2> v5 = -v2;
    assert(v5[0] == -1 && v5[1] == -2);

    // Test the operator*=
    v2 *= v3;
    assert(v2[0] == 1 && v2[1] == 4);

    // Test the operator*=
    v2 *= 2;
    assert(v2[0] == 2 && v2[1] == 8);

    // Test the operator/=
    v2 /= 2;
    assert(v2[0] == 1 && v2[1] == 4);

    // Test the operator+
    Vector<2> v6 = v2 + v3;
    assert(v6[0] == 2 && v6[1] == 6);

    // Test the operator-
    Vector<2> v7 = v2 - v3;
    assert(v7[0] == 0 && v7[1] == 2);

    // Test the operator*
    Vector<2> v8 = v2 * v3;
    assert(v8[0] == 1 && v8[1] == 8);

    // Test the operator* with scalar on the left
    Vector<2> v9 = 2 * v3;
    assert(v9[0] == 2 && v9[1] == 4);

    // Test the operator* with scalar on the right
    Vector<2> v10 = v3 * 2;
    assert(v10[0] == 2 && v10[1] == 4);

    // Test the operator/
    Vector<2> v11 = v3 / 2;
    assert(v11[0] == 0.5 && v11[1] == 1);

    // Test the operator/ with scalar on the left
    Vector<2> v12 = 2 / v3;
    assert(v12[0] == 2 && v12[1] == 1);

    // Test the sq_length function
    double sq_length = v3.sq_length();
    assert(sq_length == 5);

    // Test the length function
    double length = v3.length();
    assert(abs(length - sqrt(5)) < 1e-10);

    // Test the normalize function
    Vector<2> v13(3, 4);
    Vector<2> v14 = v13.normalize();
    assert(abs(v14.length() - 1) < 1e-10);

    // Test the dot function
    Vector<2> a(2.0, 1.0);
    Vector<2> b(3.0, -4.0);
    double actual_result = Vector<2>::dot(a, b);
    assert(actual_result == 2.0);
}

void test_Vector3() {
    // Test default constructor
    Vector<3> v1{};
    assert(v1[0] == 0.0);
    assert(v1[1] == 0.0);
    assert(v1[2] == 0.0);

    // Test constructor with parameters
    Vector<3> v2(1.0, 2.0, 3.0);
    assert(v2[0] == 1.0);
    assert(v2[1] == 2.0);
    assert(v2[2] == 3.0);

    // Test copy constructor
    Vector<3> v3(v2);
    assert(v3[0] == 1.0);
    assert(v3[1] == 2.0);
    assert(v3[2] == 3.0);

    // Test assignment operator
    v1 = v2;
    assert(v1[0] == 1.0);
    assert(v1[1] == 2.0);
    assert(v1[2] == 3.0);

    // Test addition operator
    Vector<3> v4(2.0, 3.0, 4.0);
    Vector<3> v5 = v2 + v4;
    assert(v5[0] == 3.0);
    assert(v5[1] == 5.0);
    assert(v5[2] == 7.0);

    // Test subtraction operator
    Vector<3> v6 = v4 - v2;
    assert(v6[0] == 1.0);
    assert(v6[1] == 1.0);
    assert(v6[2] == 1.0);

    // Test scalar multiplication
    Vector<3> v7 = v2 * 2.0;
    assert(v7[0] == 2.0);
    assert(v7[1] == 4.0);
    assert(v7[2] == 6.0);

    // Test scalar division
    Vector<3> v8 = v2 / 2.0;
    assert(v8[0] == 0.5);
    assert(v8[1] == 1.0);
    assert(v8[2] == 1.5);

    // Test dot product
    double dot = Vector<3>::dot(v2, v4);
    assert(std::abs(dot - 20.0) < 1e-6);

    // Test cross product
    Vector<3> cross = Vector<3>::cross(v2, v4);
    assert(cross[0] == -1.0);
    assert(cross[1] == 2.0);
    assert(cross[2] == -1.0);

    // Test magnitude
    double mag = v2.length();
    assert(std::abs(mag - std::sqrt(14.0)) < 1e-6);

    // Test normalization
    Vector<3> v9 = Vector<3>::normalized(v2);
    assert(std::abs(v9.length() - 1.0) < 1e-6);

    // Test negation
    Vector<3> v10 = -v2;
    assert(v10[0] == -1.0);
    assert(v10[1] == -2.0);
    assert(v10[2] == -3.0);

    // Test output operator
    std::cout << "v2 = " << v2 << std::endl;
}

int main() {

    test_Vector2();
    test_Vector3();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}