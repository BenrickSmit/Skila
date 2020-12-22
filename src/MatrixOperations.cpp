#include "MatrixOperations.h"

// Tested
double MatrixOperations::dot_product(Coordinate& lhs, Coordinate& rhs) {
    // This function will calculate the dot product between two coordinates and return it
    Coordinate result;
    double dot_product = 0;

    // the dot product is the multiplication of the member variables of the Coordinates
    result.set_x(lhs.get_x() * rhs.get_x());
    result.set_y(lhs.get_y() * rhs.get_y());
    result.set_z(lhs.get_z() * rhs.get_z());
    result.set_k(lhs.get_k() * rhs.get_k());

    dot_product = result.get_x() + result.get_y() + result.get_z();

    // PS: Colours not affected - Want to do some colour math later

    return dot_product;
}

// Tested - Indirectly in the test_object function for normals
Coordinate MatrixOperations::cross_product(Coordinate& lhs, Coordinate& rhs) {
    // This function will be responsible for calculating the cross product of two
    // vectors
    Coordinate result;

    // Calculate the cross-product
    result.set_x((lhs.get_y() * rhs.get_z()) - (lhs.get_z() * rhs.get_y()));
    result.set_y((lhs.get_z() * rhs.get_x()) - (lhs.get_x() * rhs.get_z()));
    result.set_z((lhs.get_x() * rhs.get_y()) - (lhs.get_y() * rhs.get_x()));

    return result;
}

bool MatrixOperations::within_plane(Coordinate& input_ray_intersection,
    std::vector<Coordinate> list_coordinates) {
    // This funciton will simply determine whether the input_plane and the lines
    // found will be on the same side. If it isn't the information should not be taken to heart
    Coordinate line_t2_t3, line_t1_t3, line_t1_t2;
    double c_t2_t3, c_t1_t3, c_t1_t2;
    bool result = true;

    // Calculate the 
    line_t2_t3 = Coordinate(list_coordinates.at(1)) - Coordinate(list_coordinates.at(2));


    // Calculat the
    line_t1_t3 = Coordinate(list_coordinates.at(0)) - Coordinate(list_coordinates.at(2));


    // Calculate the 
    line_t1_t2 = Coordinate(list_coordinates.at(0)) - Coordinate(list_coordinates.at(1));

    return result;
}

bool MatrixOperations::within_bounding_box(Coordinate& input_ray_intersection, std::vector<Coordinate> list_coordinates) {
    // This function will obtain the minimum and maximum values for the inherent
    // coordinates and determine whether the input plane is at least within the
    // bounding box of the triangle
    double min_x = 0, min_y = 0, min_z = 0, max_x = 0, max_y = 0, max_z = 0;
    bool result = true;

    // Find the minimum values
    min_x = get_min_value(list_coordinates.at(0).get_x(), list_coordinates.at(1).get_x(), list_coordinates.at(2).get_x());
    min_y = get_min_value(list_coordinates.at(0).get_y(), list_coordinates.at(1).get_y(), list_coordinates.at(2).get_y());
    min_z = get_min_value(list_coordinates.at(0).get_z(), list_coordinates.at(1).get_z(), list_coordinates.at(2).get_z());

    // Find the maximum values
    max_x = get_max_value(list_coordinates.at(0).get_x(), list_coordinates.at(1).get_x(), list_coordinates.at(2).get_x());
    max_y = get_max_value(list_coordinates.at(0).get_y(), list_coordinates.at(1).get_y(), list_coordinates.at(2).get_y());
    max_z = get_max_value(list_coordinates.at(0).get_z(), list_coordinates.at(1).get_z(), list_coordinates.at(2).get_z());

    // Determine whether the plane is within the bounding box
    // Within bounds for x
    if ((min_x > input_ray_intersection.get_x()) || (max_x < input_ray_intersection.get_x())) {
        result = false;
        return result;
    }

    // Within bounds for y
    if ((min_y > input_ray_intersection.get_y()) || (max_y < input_ray_intersection.get_y())) {
        result = false;
        return result;
    }

    // Within bounds for z
    if ((min_z > input_ray_intersection.get_z()) || (max_z < input_ray_intersection.get_z())) {
        result = false;
        return result;
    }

    return result;
}

// Tested
double MatrixOperations::get_max_value(double x, double y, double z) {
    // This function simply tests each value against the next to find the maximum
    double max = FLT_MIN;

    // Determine which is bigger, x or y
    max = x;
    if (max < y) {
        max = y;
    }

    // Determine which is bigger, x,y, or z
    if (max < z) {
        max = z;
    }

    return max;
}

// Tested
double MatrixOperations::get_min_value(double x, double y, double z) {
    // This function simply tests each value against the next to find the minimum
    double min = FLT_MAX;

    // Determine which is bigger, x or y
    min = x;
    if (min > y) {
        min = y;
    }

    // Determine which is bigger, x,y, or z
    if (min > z) {
        min = z;
    }

    return min;
}