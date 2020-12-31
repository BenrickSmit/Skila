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
    /**
     * @brief Performs the dot product on two coordinates and returns a double
     * 
     * @param lhs the Coordinate on the Left Hand Side of the operator
     * @param rhs the Coordinate on the Right Hand Side of the operator
     * @return double the value that results from the dot product
     */
    static double dot_product(Coordinate& lhs, Coordinate& rhs);
    /**
     * @brief Performs the cross product (Vector Multiplication) on two
     *          Coordinates and returns the result.
     * 
     * @param lhs the Coordinate on the Left Hand Side of the operator
     * @param rhs the Coordinate on the Right Hand Side of the operator
     * @return Coordinate the resulting Coordinate after Cross Multiplication
     */
    static Coordinate cross_product(Coordinate& lhs, Coordinate & rhs);
    /**
     * @brief Performs a simple check to determine whether the provided coordinate
     *          is within the plane created by the three coordinates
     * 
     * @param input_ray_intersection the Coordinate to check
     * @param list_coordinates the coordinates that make the triangle
     * @return true if the input is within the plane
     * @return false if the input is not within the plane
     */
    static bool within_plane(Coordinate& input_ray_intersection, 
                            std::vector<Coordinate> list_coordinates);
    /**
     * @brief Performs a simple check to determine whether the provided coordiante
     *          is within the bounding box creatd by the three coordinates
     * 
     * @param input_ray_intersection the Coordinate to check
     * @param list_coordinates the coordinates that make the triangle
     * @return true if the input is within the bounding box
     * @return false if the input is not within the bounding box
     */
    static bool within_bounding_box(Coordinate& input_ray_intersection, std::vector<Coordinate> list_coordinates);
    /**
     * @brief Get the minimum value out of a list of three values
     * 
     * @param x value one
     * @param y value two
     * @param z value three
     * @return double the value that is the least of the three
     */
    static double get_min_value(double x, double y, double z);
    /**
     * @brief Get the maximum value out of the list of three values
     * 
     * @param x value one
     * @param y value two
     * @param z value three
     * @return double the value that is the biggest of the three
     */
    static double get_max_value(double x, double y, double z);
    /**
     * @brief A simple function that performs Coordinate subtraction
     * 
     * @param lhs the value on the Left Hand Side 
     * @param rhs the avlue on the Right Hand Side
     * @return Coordinate& the Coordinate that results from the subtraction
     */
    static Coordinate& subtract(Coordinate& lhs, Coordinate& rhs);
    /**
     * @brief Get the ray lambda that is used in the calculation of the coordinate
     *          intersection
     * 
     * @param input_plane the plane to check for intersection
     * @param ray_origin the origin of the ray, often the camera
     * @param view_plane the plane that creates the image, contains a certain
     *          number of pixels
     * @return double the value of lamda for the coordinate calculations
     *          positive if it intersects with the plane, negative otherwise
     */
    static double get_ray_lambda(Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane);
    /**
     * @brief Get the ray intersection coordinate if lambda is positive
     * 
     * @param result_to_return the location of intersection of the plane and ray
     * @param input_plane the plane to check for intersection with a ray
     * @param ray_origin the origin location of the ray
     * @param view_plane the view plane through which the image is "seen"
     * @param list_coordinates the coordinates that make up the plane
     * @return true if the ray intersects with the plane
     * @return false if the ray doesn't intersect with the plane
     */
    static bool get_ray_intersection(Coordinate& result_to_return, Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane, std::vector<Coordinate> list_coordinates);
    /**
     * @brief Returns the brightness of the pixels in the image based on how
     *          far the objects are from the camera. It uses the simple 1/d rule
     * 
     * @param ray_intersection_point The coordinate where the ray intersects
     *          with the plane
     * @param ray_origin the camera location
     * @return double the pixel brightness.
     */
    static double get_ray_rasterisation(Coordinate& ray_intersection_point, Coordinate& ray_origin);
    /**
     * @brief Enables the rotation of a coordinate around the x-axis
     * 
     * @param input the Coordinate to rotate
     * @param angle the angle at which to rotate
     * @return Coordinate& the resulting Coordinate
     */
    static Coordinate& rotate_x(Coordinate& input, double angle);
    /**
     * @brief Enables the rotation of a coordinate around the y-axis
     * 
     * @param input the Coordinate to rotate
     * @param angle the angle at which to rotate
     * @return Coordinate& the resulting Coordinate
     */
    static Coordinate& rotate_y(Coordinate& input, double angle);
    /**
     * @brief Enables the rotation of a coordinate around the z-axis
     * 
     * @param input the Coordinate to rotate
     * @param angle the angle at which to rotate
     * @return Coordinate& the resulting Coordinate
     */
    static Coordinate& rotate_z(Coordinate& input, double angle);
    /**
     * @brief Get the colour of the ray returned into the camera. This helps 
     *          determine the colour of the object based on its location, etc
     * 
     * @param input the Intersection Coordinate
     * @param ray_rasterisation the pixel brightness based on distance
     * @return std::vector<uint16_t> the individual RGBA values that determine
     *              the colour
     */
    static std::vector<uint16_t> get_ray_colour(Coordinate& input, double ray_rasterisation);
    /**
     * @brief Get the barycentric coordinates of the input intersection 
     *          coordinate to help with the calculation of the colours. The 
     *          values will always add up to 1.0f if within the plane
     * 
     * @param input the intersection coordinate to use
     * @param list_coordinates the coordinates that make the triangle
     * @return std::vector<float>& the resulting alpha, beta, and gamma values
     *          that represent the Barycentric Coordinates
     */
    static std::vector<float>& get_barycentric_coordinates(Coordinate& input, std::vector<Coordinate>& list_coordinates);
    /**
     * @brief Returns the RGBA colour values based on the found barycentric 
     *          coordinates
     * 
     * @param barycentric_coordinates the alpha, beta, and Gamma coordinates 
     *          that determine the weight of each coordinate's colour on the
     *          resulting colour
     * @param list_coordinates the coordinates that make the triangle that's
     *          intersected
     * @return std::vector<uint16_t>& the resulting RGBA value of that point
     */
    static std::vector<uint16_t>& get_barycentric_colours(std::vector<float>& barycentric_coordinates, std::vector<Coordinate>& list_coordinates);
    /**
     * @brief Enables the rounding of doubles to certain decimals for accuracy
     *          of calculations
     * 
     * @param input the input value
     * @param decimals the number of decimals required. Zero decimals makes an 
     *          integer
     * @return double the resulting double after rounding
     */
    static double round(double input, int decimals = 4);
    /**
     * @brief Enables the conversion of degrees to radians to ensure correct
     *          calculations of rotations
     * 
     * @param input_angle the angle to convert to radians
     * @return double the resulting radian made from the angle
     */
    static double to_radians(double input_angle);
private:
    // Member Variables
    static const float PI;  //3.14159265...
};