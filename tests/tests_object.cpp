#include "gtest/gtest.h"

#include "Coordinate.h"
#include "Object.h"

TEST(TEST_OBJECT_SUITE, calculate_object_normals_InputTestInput_CorrectNormalResultReturn) {
    Coordinate x{-1,0,2}, y{1,0,2}, z{0,-1,3};
    Object test_data;
    Coordinate expected_normal{0,-2,-2};

    // Add the data, and compare
    test_data.add_triangle(x,y,z);
    expected_normal.set_k(4);           // Due to the addition of the automatic function

    EXPECT_EQ(test_data.get_normal(), expected_normal);
}

TEST(TEST_OBJECT_SUITE, calculate_vector_plane_InputTestInput_CorrectKResultReturn) {
    Coordinate x{-1,0,2}, y{1,0,2}, z{0,-1,3};
    Object test_data;
    double expected_k{4};

    // Add the data, and compare
    test_data.add_triangle(x,y,z);

    EXPECT_EQ(test_data.get_normal().get_k(), expected_k);
}
//\todo: Test other functions

TEST(TEST_OBJECT_SUITE, get_plane_InputTestInput_CorrectVectorReturn) {
    Coordinate x{-1,0,2}, y{1,0,2}, z{0,-1,3};
    Object test_data;
    std::vector<double> expected_plane{0,-2,-2,4};

    // Add the data, and compare
    test_data.add_triangle(x,y,z);

    EXPECT_EQ(test_data.get_plane(), expected_plane);
}

TEST(TEST_OBJECT_SUITE, get_points_InputTestInput_CorrectVectorOfCoordinatesReturn) {
    Coordinate x{-1,0,2}, y{1,0,2}, z{0,-1,3};
    Object test_data;
    std::vector<Coordinate> expected_points{x,y,z};
    std::vector<Coordinate> test_return;

    // Add the data, and compare
    test_data.add_triangle(x,y,z);
    test_return = test_data.get_points();

    EXPECT_EQ(test_return, expected_points);
}

