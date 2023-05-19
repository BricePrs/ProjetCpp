/**
 * Handles the tests for the Vector Class.
 * The other classes (Universe, Particle, Grid) are tested along
 * the different labs.
 */

#include <iostream>
#include <cmath>
#include "Vector.h"

#include <gtest/gtest.h>


TEST(TestVector2, TestConstructors) {
    // Test the default constructor
    Vector<2> v1;
    EXPECT_NEAR(v1[0], 0.0, 1e-20);
    EXPECT_NEAR(v1[1], 0.0, 1e-20);

    // Test the parameterized constructor
    Vector<2> v2(1.0, 2.0);
    EXPECT_NEAR(v2[0], 1.0, 1e-20);
    EXPECT_NEAR(v2[1], 2.0, 1e-20);

    // Test the copy constructor
    Vector<2> v3(v2);
    EXPECT_NEAR(v3[0], 1.0, 1e-20);
    EXPECT_NEAR(v3[1], 2.0, 1e-20);
}

TEST(TestVector2, TestMethods) {

    Vector<2> v2(1.0, 2.0);
    Vector<2> v3(v2);

    // Test the zero function
    Vector<2> v4 = Vector<2>::zero();
    EXPECT_NEAR(v4[0], 0.0, 1e-20);
    EXPECT_NEAR(v4[1], 0.0, 1e-20);

    // Test the sq_length function
    double sq_length = v3.sq_length();
    EXPECT_NEAR(sq_length, 5.0, 1e-20);

    // Test the length function
    double length = v3.length();
    EXPECT_LT(abs(length - sqrt(5)), 1e-10);

    // Test the normalize function
    Vector<2> v13(3, 4);
    Vector<2> v14 = v13.normalize();
    EXPECT_LT(abs(v14.length() - 1), 1e-10);


    // Test the dot function
    Vector<2> a(2.0, 1.0);
    Vector<2> b(3.0, -4.0);
    double actual_result = Vector<2>::dot(a, b);
    EXPECT_NEAR(actual_result, 2.0, 1e-20);

}
TEST(TestVector2, TestOperators) {
    // Test the operator<<
    Vector<2> v2(1.0, 2.0);
    std::cout << "v2 = " << v2 << std::endl;

    // Test the operator+=
    Vector<2> v3(v2);
    v2 += v3;
    EXPECT_NEAR(v2[0], 2.0, 1e-20);
    EXPECT_NEAR(v2[1], 4.0, 1e-20);
    // Test the operator-=
    v2 -= v3;
    EXPECT_NEAR(v2[0], 1.0, 1e-20);
    EXPECT_NEAR(v2[1], 2.0, 1e-20);

    // Test the operator-
    Vector<2> v5 = -v2;
    EXPECT_NEAR(v5[0], -1.0, 1e-20);
    EXPECT_NEAR(v5[1], -2.0, 1e-20);

    // Test the operator*=
    v2 *= v3;
    EXPECT_NEAR(v2[0], 1.0, 1e-20);
    EXPECT_NEAR(v2[1], 4.0, 1e-20);

    // Test the operator*=
    v2 *= 2;
    EXPECT_NEAR(v2[0], 2.0, 1e-20);
    EXPECT_NEAR(v2[1], 8.0, 1e-20);

    // Test the operator/=
    v2 /= 2;
    EXPECT_NEAR(v2[0], 1.0, 1e-20);
    EXPECT_NEAR(v2[1], 4.0, 1e-20);

    // Test the operator+
    Vector<2> v6 = v2 + v3;
    EXPECT_NEAR(v6[0], 2.0, 1e-20);
    EXPECT_NEAR(v6[1], 6.0, 1e-20);

    // Test the operator-
    Vector<2> v7 = v2 - v3;
    EXPECT_NEAR(v7[0], 0.0, 1e-20);
    EXPECT_NEAR(v7[1], 2.0, 1e-20);

    // Test the operator*
    Vector<2> v8 = v2 * v3;
    EXPECT_NEAR(v8[0], 1.0, 1e-20);
    EXPECT_NEAR(v8[1], 8.0, 1e-20);

    // Test the operator* with scalar on the left
    Vector<2> v9 = 2 * v3;
    EXPECT_NEAR(v9[0], 2.0, 1e-20);
    EXPECT_NEAR(v9[1], 4.0, 1e-20);

    // Test the operator* with scalar on the right
    Vector<2> v10 = v3 * 2;
    EXPECT_NEAR(v10[0], 2.0, 1e-20);
    EXPECT_NEAR(v10[1], 4.0, 1e-20);

    // Test the operator/
    Vector<2> v11 = v3 / 2;
    EXPECT_NEAR(v11[0], 0.5, 1e-20);
    EXPECT_NEAR(v11[1], 1.0, 1e-20);

    // Test the operator/ with scalar on the left
    Vector<2> v12 = 2 / v3;
    EXPECT_NEAR(v12[0], 2.0, 1e-20);
    EXPECT_NEAR(v12[1], 1.0, 1e-20);
}

TEST(TestVector3, TestConstructors) {
    // Test default constructor
    Vector<3> v1{};
    EXPECT_NEAR(v1[0], 0.0, 1e-20);
    EXPECT_NEAR(v1[1], 0.0, 1e-20);
    EXPECT_NEAR(v1[2], 0.0, 1e-20);

    // Test constructor with parameters
    Vector<3> v2(1.0, 2.0, 3.0);
    EXPECT_NEAR(v2[0], 1.0, 1e-20);
    EXPECT_NEAR(v2[1], 2.0, 1e-20);
    EXPECT_NEAR(v2[2], 3.0, 1e-20);

    // Test copy constructor
    Vector<3> v3(v2);
    EXPECT_NEAR(v3[0], 1.0, 1e-20);
    EXPECT_NEAR(v3[1], 2.0, 1e-20);
    EXPECT_NEAR(v3[2], 3.0, 1e-20);
}
TEST(TestVector3, TestOperators) {

    Vector<3> v1{};
    Vector<3> v2(1.0, 2.0, 3.0);

    // Test assignment operator
    v1 = v2;
    EXPECT_NEAR(v1[0], 1.0, 1e-20);
    EXPECT_NEAR(v1[1], 2.0, 1e-20);
    EXPECT_NEAR(v1[2], 3.0, 1e-20);

    // Test addition operator
    Vector<3> v4(2.0, 3.0, 4.0);
    Vector<3> v5 = v2 + v4;
    EXPECT_NEAR(v5[0], 3.0, 1e-20);
    EXPECT_NEAR(v5[1], 5.0, 1e-20);
    EXPECT_NEAR(v5[2], 7.0, 1e-20);

    // Test subtraction operator
    Vector<3> v6 = v4 - v2;
    EXPECT_NEAR(v6[0], 1.0, 1e-20);
    EXPECT_NEAR(v6[1], 1.0, 1e-20);
    EXPECT_NEAR(v6[2], 1.0, 1e-20);

    // Test scalar multiplication
    Vector<3> v7 = v2 * 2.0;
    EXPECT_NEAR(v7[0], 2.0, 1e-20);
    EXPECT_NEAR(v7[1], 4.0, 1e-20);
    EXPECT_NEAR(v7[2], 6.0, 1e-20);

    // Test scalar division
    Vector<3> v8 = v2 / 2.0;
    EXPECT_NEAR(v8[0], 0.5, 1e-20);
    EXPECT_NEAR(v8[1], 1.0, 1e-20);
    EXPECT_NEAR(v8[2], 1.5, 1e-20);

    // Test negation
    Vector<3> v10 = -v2;
    EXPECT_NEAR(v10[0], -1.0, 1e-20);
    EXPECT_NEAR(v10[1], -2.0, 1e-20);
    EXPECT_NEAR(v10[2], -3.0, 1e-20);

    // Test output operator
    std::cout << "v2 = " << v2 << std::endl;
}

TEST(Testvector3, TestMethods) {
    Vector<3> v2(1.0, 2.0, 3.0);
    Vector<3> v4(2.0, 3.0, 4.0);


    // Test dot product
    double dot = Vector<3>::dot(v2, v4);
    EXPECT_LT(std::abs(dot - 20.0), 1e-6);

    // Test cross product
    Vector<3> cross = Vector<3>::cross(v2, v4);
    EXPECT_NEAR(cross[0], -1.0, 1e-20);
    EXPECT_NEAR(cross[1], 2.0, 1e-20);
    EXPECT_NEAR(cross[2], -1.0, 1e-20);

    // Test magnitude
    double mag = v2.length();
    EXPECT_LT(std::abs(mag - std::sqrt(14.0)) , 1e-6);


    // Test normalization
    Vector<3> v9 = Vector<3>::normalized(v2);
    EXPECT_LT(std::abs(v9.length() - 1.0) , 1e-6);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}