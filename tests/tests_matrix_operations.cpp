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
	// Find the value of lambda for a given set of default points and the triangle
	// that they form.

	// PS: This specifies a lambda that directly hits a triangle formed by the plane. It should
	//		return a colour once all calculations are complete.

	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (2-2)), (1.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	plane.set_plane(triangle.get_plane());
	double lambda = -1;
	lambda = MatrixOperations::get_ray_lambda(plane, ray_origin, view_plane);

	// Returning a Lambda bigger than zero means the ray intersects the plane
	EXPECT_GE(lambda, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_lambda_CoordinatesOnPlaneBehindCameraInput_ReturnLambdaNegative) {
	// Find the value of lambda for a given set of default points and the triangle
	// that they form.

	// PS: With this the camera is behind the triangle formed, and although the ray does intersect
	// 		with the triangle, lambda is negative, indicating it is behidn the camera/ray origin, 
	//		and thus not necessary to take into consideration

	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,4,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (2-2)), (5.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	plane.set_plane(triangle.get_plane());
	double lambda = -1;
	lambda = MatrixOperations::get_ray_lambda(plane, ray_origin, view_plane);

	// Returning a Lambda bigger than zero means the ray intersects the plane
	EXPECT_LT(lambda, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_lambda_CoordinatesOutsidePlaneInput_ReturnLambdaGreaterOrEqualZero) {
	// Find the value of lambda for a given set of default points and the triangle
	// that they form.

	// PS: view_plane here is specified as the leftmost pixel on the middle row of the viewplane
	//		it is not meant to return a value and should return black as a the colour should
	
	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (0-2)), (0.1 * (0-2)), (1.0)};		// Used for the view_plane -> 
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	plane.set_plane(triangle.get_plane());
	double lambda = -1;
	lambda = MatrixOperations::get_ray_lambda(plane, ray_origin, view_plane);

	// Returning a Lambda bigger than zero means the ray intersects the plane
	EXPECT_GE(lambda, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_intersection_CoordinateOnPlaneInput_ReturnTrueWithinBoundingBox) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (1.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	// Returning a Lambda bigger than zero means the ray intersects the plane
	EXPECT_EQ(true, static_cast<bool>(is_intersected));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_intersection_CoordinateOutsidePlaneInput_ReturnFalseWithinBoundingBox) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (0-2)), (0.1 * (0-2)), (1.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	// Returning a Lambda bigger than zero means the ray intersects the plane
	EXPECT_EQ(false, static_cast<bool>(is_intersected));
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, rotate_x_TwoThreeFourAndNinetyDegreesInput_ReturnTwoMinusFourThree) {
	Coordinate point{2,-2,4};
	Coordinate expected_result{2,2,4};
	EXPECT_EQ(MatrixOperations::rotate_x(point, 90).get_rounded(), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, rotate_x_TwoThreeFourAndThreeNinetyDegreesInput_ReturnTwoMinusThreeFloatTwoFloat) {
	Coordinate point{2,-2,4};
	Coordinate expected_result{2,2,4};

	EXPECT_EQ(MatrixOperations::rotate_x(point, 450).get_rounded(), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, rotate_y_TwoMinusFourThreeAndNinetyDegreesInput_ReturnFourThreeZero) {
	Coordinate point{2,-4,3};
	Coordinate expected_result{3,-4,-2};
	EXPECT_EQ(MatrixOperations::rotate_y(point, 90).get_rounded(), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, rotate_y_TwoMinusFourThreeAndFourFiftyDegreesInput_ReturnFourThreeZero) {
	Coordinate point{2,-4,3};
	Coordinate expected_result{3,-4,-2};

	EXPECT_EQ(MatrixOperations::rotate_y(point, 450).get_rounded(), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, rotate_z_OneZeroZeroAndNinetyDegreesInput_ReturnZeroOneZero) {
	Coordinate point{1,0,0};
	Coordinate expected_result{0,1,0};

	EXPECT_EQ(MatrixOperations::rotate_z(point, 90).get_rounded(), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, rotate_z_OneZeroZeroAndFourFiftyDegreesInput_ReturnZeroOneZero) {
	Coordinate point{1,0,0};
	Coordinate expected_result{0,1,0};

	EXPECT_EQ(MatrixOperations::rotate_z(point, 450).get_rounded(), expected_result);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, round_TwoPointThreeToNineAndZeroDecimalsInput_ReturnTwo) {
	EXPECT_EQ(MatrixOperations::round(2.3456789,0), 2);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, round_TwoPointThreeToNineAndTwoDecimalsInput_ReturnTwoPointThreeFive) {
	EXPECT_EQ(MatrixOperations::round(2.3456789,2), 2.35);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, round_TwoPointThreeToNineAndFourDecimalsInput_ReturnTwoPointThreeFourFiveSeven) {
	EXPECT_EQ(MatrixOperations::round(2.3456789), 2.3457);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_rasterisation_DefaultRayOriginAndIntersectionCoordinateInput_ReturnDefaultResultBetweenZeroAndOne) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
	}

	EXPECT_LE(brightness_value, 1.00);
	EXPECT_GE(brightness_value, 0.00);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_rasterisation_DefaultIntersectionAndRayOriginInput_ReturnColourBetweenZeroAndTwoFiftyFive) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (1.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	int colour_value = -1;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		colour_value = 255 * brightness_value;
	}

	EXPECT_LE(colour_value, 255);
	EXPECT_GE(colour_value, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_rasterisation_FurtherViewPlaneInput_ReturnColourBetweenZeroAndTwoFiftyFive) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2}, y{1.0,0,2}, z{0.0,-1,3};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	int colour_value = -1;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		colour_value = 255 * brightness_value;
	}

	EXPECT_LE(colour_value, 255);
	EXPECT_GE(colour_value, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_rasterisation_FurtherPlaneInput_ReturnColourBetweenZeroAndHundred) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,5}, y{1.0,0,5}, z{0.0,-1,6};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	int colour_value = -1;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		colour_value = 255 * brightness_value;
	}

	EXPECT_LE(colour_value, 100);
	EXPECT_GE(colour_value, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_rasterisation_FurthestPlaneInput_ReturnColourBlack) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,9}, y{1.0,0,8}, z{0.0,-1,9};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	int colour_value = -1;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		colour_value = 255 * brightness_value;
	}

	EXPECT_LE(colour_value, 30);	// Less than 40 is basically black
	EXPECT_GE(colour_value, 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_colour_RedInput_ReturnColourBetweenZeroAndTwoFiftyFive) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,9, 255, 0, 0, 255}, y{1.0,0,8, 255, 0, 0, 255}, z{0.0,-1,9, 255, 0, 0, 255};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		result.set_colour(MatrixOperations::get_ray_colour(result, brightness_value));
	}

	EXPECT_LE(result.get_colour().at(0), 255);
	EXPECT_LE(result.get_colour().at(1), 255);
	EXPECT_LE(result.get_colour().at(2), 255);
	EXPECT_GE(result.get_colour().at(0), 0);
	EXPECT_GE(result.get_colour().at(1), 0);
	EXPECT_GE(result.get_colour().at(2), 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_colour_GreenInput_ReturnColourBetweenZeroAndTwoFiftyFive) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,9,0, 255, 0, 255}, y{1.0,0,8,0, 255, 0, 255}, z{0.0,-1,9,0, 255, 0, 255};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		result.set_colour(MatrixOperations::get_ray_colour(result, brightness_value));
	}

	EXPECT_LE(result.get_colour().at(0), 255);
	EXPECT_LE(result.get_colour().at(1), 255);
	EXPECT_LE(result.get_colour().at(2), 255);
	EXPECT_GE(result.get_colour().at(0), 0);
	EXPECT_GE(result.get_colour().at(1), 0);
	EXPECT_GE(result.get_colour().at(2), 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_colour_BlueInput_ReturnColourBetweenZeroAndTwoFiftyFive) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2, 0, 0, 255, 255}, y{1.0,0,2, 0, 0, 255, 255}, z{0.0,-1,3, 0, 0, 255, 255};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		result.set_colour(MatrixOperations::get_ray_colour(result, brightness_value));
	}

	EXPECT_LE(result.get_colour().at(0), 255);
	EXPECT_LE(result.get_colour().at(1), 255);
	EXPECT_LE(result.get_colour().at(2), 255);
	EXPECT_GE(result.get_colour().at(0), 0);
	EXPECT_GE(result.get_colour().at(1), 0);
	EXPECT_GE(result.get_colour().at(2), 0);
}

TEST(TEST_MATRIX_OPERATIONS_SUITE, get_ray_colour_RGBInput_ReturnMixedColourBetweenZeroAndTwoFiftyFive) {
	// Find out whether a given camera/ray origin, view plane and triangle intersect
	Coordinate x{-1.0,0,2, 0, 0, 255, 255}, y{1.0,0,2, 0, 255, 0, 255}, z{0.0,-1,3, 255, 0, 0, 255};				// Creates the plane
	Coordinate ray_origin{0.0,-1,-1};								// Used for the camera and ray origin
	Coordinate view_plane{(0.1 * (2-2)), (0.1 * (4-2)), (2.0)};	// Used for the view_plane
	
	Object triangle;
	triangle.add_triangle(x,y,z);
	triangle.calculate_object_normal();	// Not really necessary, done implicitly
	triangle.calculate_vector_plane(); // Not really necessary, done implicitly
	
	//Double value
	Coordinate plane;
	Coordinate result;
	plane.set_plane(triangle.get_plane());
	double is_intersected = false;
	is_intersected = MatrixOperations::get_ray_intersection(result, plane, ray_origin, view_plane, triangle.get_points());

	double brightness_value = -1.0;
	if(is_intersected) {
		brightness_value = MatrixOperations::get_ray_rasterisation(result, ray_origin);
		result.set_colour(MatrixOperations::get_ray_colour(result, brightness_value));
	}

	EXPECT_LE(result.get_colour().at(0), 255);
	EXPECT_LE(result.get_colour().at(1), 255);
	EXPECT_LE(result.get_colour().at(2), 255);
	EXPECT_GE(result.get_colour().at(0), 0);
	EXPECT_GE(result.get_colour().at(1), 0);
	EXPECT_GE(result.get_colour().at(2), 0);
}



