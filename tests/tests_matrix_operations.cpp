#include "gtest/gtest.h"

#include "Coordinate.h"
#include "MatrixOperations.h"

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_min_value_OneTwoMinusTwo_ReturnZMinusTwo) {
	double x{1}, y{2}, z{-2};
	double expected_result = -2;
	EXPECT_EQ(MatrixOperations::get_min_value(x,y,z), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_min_value_OneTwoMinusTwo_ReturnYMinusTwo) {
	double x{1}, y{-2}, z{2};
	double expected_result = -2;
	EXPECT_EQ(MatrixOperations::get_min_value(x, y, z), expected_result );
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_min_value_OneTwoMinusTwo_ReturnXMinusTwo) {
	double x{-2}, y{1}, z{2};
	double expected_result = -2;
	EXPECT_EQ(MatrixOperations::get_min_value(x, y, z), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_max_value_OneTwoMinusTwo_ReturnZTwo) {
	double x{ 1 }, y{ -2 }, z{ 2 };
	double expected_result = 2;
	EXPECT_EQ(MatrixOperations::get_max_value(x, y, z), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_max_value_OneTwoMinusTwo_ReturnYTwo) {
	double x{ 1 }, y{ 2 }, z{ -2 };
	double expected_result = 2;
	EXPECT_EQ(MatrixOperations::get_max_value(x, y, z), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_max_value_OneTwoMinusTwo_ReturnXTwo) {
	double x{ 2 }, y{ 1 }, z{ -2 };
	double expected_result = 2;
	EXPECT_EQ(MatrixOperations::get_max_value(x, y, z), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, dot_product_NineTwoSevenAndFourEightTenInput_ReturnHundredTwentyTwo) {
	Coordinate x{9,2,7}, y{4,8,10};
	double expected_result = 122;
	EXPECT_EQ(expected_result, MatrixOperations::dot_product(x,y));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, dot_product_OneTwoThreeAndFourMinusFiveInput_ReturnTwelve) {
	Coordinate x{ 1,2,3 }, y{ 4,-5,6 };
	double expected_result = 12;
	EXPECT_EQ(expected_result, MatrixOperations::dot_product(x, y));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, dot_product_SixMinusOneThreeAndFourEighteenMinusTwoInput_ReturnZero) {
	Coordinate x{6,-1,3}, y{4,18,-2};
	double expected_result = 0;
	EXPECT_EQ(expected_result, MatrixOperations::dot_product(x, y));
}

