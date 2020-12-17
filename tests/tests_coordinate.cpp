#include <vector>

#include "gtest/gtest.h"

#include "Coordinate.h"

// Coordinate Test Suite
// Coordinate Accept Cooridinates
TEST(TEST_COORDINATE_SUITE, ctor_OriginCoordinateAsIntInput_ExpectGettersAsZero) {
  Coordinate coord{0,0,0};

  EXPECT_EQ(0, coord.get_x());
  EXPECT_EQ(0, coord.get_y());
  EXPECT_EQ(0, coord.get_z());
}

TEST(TEST_COORDINATE_SUITE, ctor_OriginCoordinateAsVectorInput_ExpectGettersAsZero) {
  Coordinate coord = Coordinate(std::vector<double>({0,0,0}));

  EXPECT_EQ(0, coord.get_x());
  EXPECT_EQ(0, coord.get_y());
  EXPECT_EQ(0, coord.get_z());
}

TEST(TEST_COORDINATE_SUITE, ctor_BlackAsIntInput_ExpectGettersAsZero) {
  Coordinate coord{0,0,0,255};

  EXPECT_EQ(0, coord.get_r());
  EXPECT_EQ(0, coord.get_g());
  EXPECT_EQ(0, coord.get_b());
  EXPECT_EQ(255, coord.get_a());
}

TEST(TEST_COORDINATE_SUITE, ctor_BlackAsVectorInput_ExpectGettersAsZero) {
  Coordinate coord = Coordinate(std::vector<uint16_t>({0,0,0,255}));

  EXPECT_EQ(0, coord.get_r());
  EXPECT_EQ(0, coord.get_g());
  EXPECT_EQ(0, coord.get_b());
  EXPECT_EQ(255, coord.get_a());
}

TEST(TEST_COORDINATE_SUITE, ctor_OriginCoordinateAndBlackAsIntInput_ExpectGettersAsZero) {
  Coordinate coord{0,0,0,0,0,0,255};

  EXPECT_EQ(0.0, coord.get_x());
  EXPECT_EQ(0.0, coord.get_y());
  EXPECT_EQ(0.0, coord.get_z());
  EXPECT_EQ(0, coord.get_r());
  EXPECT_EQ(0, coord.get_g());
  EXPECT_EQ(0, coord.get_b());
  EXPECT_EQ(255, coord.get_a());
}

TEST(TEST_COORDINATE_SUITE, ctor_OriginCoordinateAndBlackAsVectorInput_ExpectGettersAsZero) {
  Coordinate coord = Coordinate(std::vector<double>({0,0,0}), std::vector<uint16_t>({0,0,0,255}));

  EXPECT_EQ(0, coord.get_x());
  EXPECT_EQ(0, coord.get_y());
  EXPECT_EQ(0, coord.get_z());
  EXPECT_EQ(0, coord.get_r());
  EXPECT_EQ(0, coord.get_g());
  EXPECT_EQ(0, coord.get_b());
  EXPECT_EQ(255, coord.get_a());
}

TEST(TEST_COORDINATE_SUITE, get_colour_WhiteColourInput_ExpectWhiteColourReturn) {
  std::vector<uint16_t> expected_colour = std::vector<uint16_t>({255,255,255,255});
  Coordinate coord = Coordinate(expected_colour);

  EXPECT_EQ(coord.get_colour(), expected_colour);
}

TEST(TEST_COORDINATE_SUITE, get_coordinate_NegativeOneInput_ExpectNegativeOneReturn) {
  std::vector<double> expected_point = std::vector<double>({-1.1,-1.1,-1.1});
  Coordinate coord = Coordinate(expected_point);

  EXPECT_EQ(coord.get_coordinate(), expected_point);
}

TEST(TEST_COORDINATE_SUITE, set_colour_HigherThan255Input_Expect255Return) {
  std::vector<uint16_t> input_colour = std::vector<uint16_t>({300,300,300,300});
  std::vector<uint16_t> expected_colour = std::vector<uint16_t>({255,255,255,255});
  Coordinate coord = Coordinate(input_colour);

  EXPECT_EQ(coord.get_colour(), expected_colour);
}

TEST(TEST_COORDINATE_SUITE, set_colour_LowerThan0Input_Expect0Return) {
  // Technically Impossibel due to "unsigned int" but still testable
  std::vector<uint16_t> input_colour = std::vector<uint16_t>({0,0,0,0});
  std::vector<uint16_t> expected_colour = std::vector<uint16_t>({0,0,0,0});
  Coordinate coord = Coordinate(input_colour);

  EXPECT_EQ(coord.get_colour(), expected_colour);
}

TEST(TEST_COORDINATE_SUITE, operatorPlusOverload_AddPositiveUnitVectors_ExpectDoubleUnitVectorReturn) {
  Coordinate coord1{1,1,1},coord2{1,1,1};
  Coordinate expected_result{2,2,2};
  EXPECT_EQ((coord1+coord2).get_coordinate(), expected_result.get_coordinate());
}

TEST(TEST_COORDINATE_SUITE, operatorPlusOverload_AddPosUnitAndNegUnitVectors_ExpectZeroReturn) {
  Coordinate coord1{1,1,1},coord2{-1,-1,-1};
  Coordinate expected_result{0,0,0};
  EXPECT_EQ((coord1+coord2).get_coordinate(), expected_result.get_coordinate());
}

TEST(TEST_COORDINATE_SUITE, operatorMinusOverload_SubtractUnitVectors_ExpectZeroAsUnitVectorReturn) {
  Coordinate coord1{1,1,1},coord2{1,1,1};
  Coordinate expected_result{0,0,0};
  EXPECT_EQ((coord1-coord2).get_coordinate(), expected_result.get_coordinate());
}

TEST(TEST_COORDINATE_SUITE, operatorMinusOverload_SubtractPosAndNegUnitVectors_ExpectDoubleUnitVectorReturn) {
  Coordinate coord1{1,1,1},coord2{-1,-1,-1};
  Coordinate expected_result{2,2,2};
  EXPECT_EQ((coord1-coord2).get_coordinate(), expected_result.get_coordinate());
}

TEST(TEST_COORDINATE_SUITE, operatorEqualOverload_UnitVectors_ExpectTrueReturn) {
  Coordinate coord1{1,1,1}, coord2{1,1,1};
  EXPECT_EQ(true, coord1==coord2);
}

TEST(TEST_COORDINATE_SUITE, operatorEqualOverload_OriginVectorAndUnitVectorEquality_ExpectFalseReturn) {
  Coordinate coord1{0,0,0}, coord2{1,1,1};
  EXPECT_EQ(false, coord1==coord2);
}

TEST(TEST_COORDINATE_SUITE, OperatorInequalOverload_OriginVectorAndUnitVectorInequality_ExpectTrueReturn) {
  Coordinate coord1{0,0,0}, coord2{1,1,1};
  EXPECT_EQ(true, coord1!=coord2);
}

TEST(TEST_COORDINATE_SUITE, scalar_multiply_UnitVectorInput_DoubleUnitVectorReturned) {
  Coordinate coord1{1,1,1}, coord2{1.1,1.1,1.1}, expected_output1{2,2,2}, 
  expected_output2{2.2,2.2,2.2};

  coord1 = coord1.scalar_multiply(2);
  coord2 = coord2.scalar_multiply(2);

  EXPECT_EQ(coord1.get_coordinate(), expected_output1.get_coordinate());
  EXPECT_EQ(coord2.get_coordinate(), expected_output2.get_coordinate());
}

TEST(TEST_COORDINATE_SUITE, scalar_multiply_UnitVectorInput_NegativeUnitVectorReturned) {
  Coordinate coord1{1,1,1}, expected_output{-1,-1,-1};

  coord1 = coord1.scalar_multiply(-1);

  EXPECT_EQ(coord1.get_coordinate(), expected_output.get_coordinate());
}