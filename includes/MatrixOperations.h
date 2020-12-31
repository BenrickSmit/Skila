/** @brief This class is used to enable all the more difficult processing
 *          required in ray tracing. It contains methods that help with
 *          barycentric colours, and more.
 *  @author B.G. Smit
 *  @date 9/12/2020
*/

#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <cfloat>

#include "Coordinate.h"

class MatrixOperations {
public:
    static double dot_product(Coordinate& lhs, Coordinate& rhs);
    static Coordinate cross_product(Coordinate& lsh, Coordinate & rhs);
    static bool within_plane(Coordinate& input_ray_intersection, std::vector<Coordinate> list_coordinates);
    static bool within_bounding_box(Coordinate& input_ray_intersection, std::vector<Coordinate> list_coordinates);
    static double get_min_value(double x, double y, double z);
    static double get_max_value(double x, double y, double z);
    static Coordinate& subtract(Coordinate& lhs, Coordinate& rhs);
    static double get_ray_lambda(Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane);
    static bool get_ray_intersection(Coordinate& result_to_return, Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane, std::vector<Coordinate> list_coordinates);
    static double get_ray_rasterisation(Coordinate& ray_intersection_point, Coordinate& ray_origin);
    static Coordinate& rotate_x(Coordinate& input, double angle);
    static Coordinate& rotate_y(Coordinate& input, double angle);
    static Coordinate& rotate_z(Coordinate& input, double angle);
    static std::vector<uint16_t> get_ray_colour(Coordinate& input, double ray_rasterisation);
    static std::vector<float>& get_barycentric_coordinates(Coordinate& input, std::vector<Coordinate>& list_coordinates);
    static std::vector<uint16_t>& get_barycentric_colours(std::vector<float>& barycentric_coordinates, std::vector<Coordinate>& list_coordinates);
    static double round(double input, int decimals = 4);
    static double to_radians(double input_angle);
private:
    // Member Variables
    static const float PI;
};