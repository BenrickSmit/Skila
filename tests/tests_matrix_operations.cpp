#include "gtest/gtest.h"

#include "Coordinate.h"
#include "MatrixOperations.h"
#include "Object.h"

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

TEST(TEST_MATRIX_OPERATIONS_SUITE, subtract_SevenMinusMinusSeven_ReturnFourteen) {
	Coordinate x{7,7,7}, y{-7,-7,-7};
	Coordinate expected_result{14,14,14};
	EXPECT_EQ(expected_result, MatrixOperations::subtract(x,y));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, subtract_SevenMinusSeven_ReturnZero) {
	Coordinate x{7,7,7}, y{7,7,7};
	Coordinate expected_result{0,0,0};
	EXPECT_EQ(expected_result, MatrixOperations::subtract(x,y));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, subtract_SevenMinusZero_ReturnSeven) {
	Coordinate x{7,7,7}, y{0,0,0};
	Coordinate expected_result{7,7,7};
	EXPECT_EQ(expected_result, MatrixOperations::subtract(x,y));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_lambda_CoordinatesOnPlaneInput_ReturnLambdaBiggerThanEqualZero) {
	Coordinate x{-1,0,2},y{1,0,2},z{0,-3,3};
	// the test view plane is a 5x5 grid, 2.2.1 is in the middle
	Coordinate view_plane_m{0.1*(2-2),0.1*(2-2),1}, camera_position_ray_origin{0,-1,-1};
	Coordinate input_plane;

	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_vector_plane();
	input_plane = triangle.get_plane();
	EXPECT_GE(MatrixOperations::get_ray_lambda(input_plane, camera_position_ray_origin, view_plane_m), 0);
}


TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_lambda_CoordinatesOutsidePlaneInput_ReturnLambdaLessThanZero) {
	Coordinate x{-1,0,2},y{1,0,2},z{0,-3,3};
	// the test view plane is a 5x5 grid, 4.4.1 is in the middle
	Coordinate view_plane_m{0.1*(4-2),0.1*(4-2),1}, camera_position_ray_origin{0,-1,-1};
	Coordinate input_plane;

	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_vector_plane();
	input_plane = triangle.get_plane();
	EXPECT_LT(MatrixOperations::get_ray_lambda(input_plane, camera_position_ray_origin, view_plane_m), 0);
}