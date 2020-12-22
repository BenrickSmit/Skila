/** @brief Dummy class used for illustration purposes. Doing something with it.

    Detailed description follows here.
    For more examples of doxygen comments, look here [https://www.doxygen.nl/manual/docblocks.html] and
    [https://flcwiki.desy.de/How%20to%20document%20your%20code%20using%20doxygen]

    @author X. XYZ, DESY
    @date March 2008

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
private:
    // Not really required
};