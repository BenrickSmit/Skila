/** @brief This class is responsible for creating triangular objects used in the
 *          creation of other objects such as spheres, pyramids, etc. It only
 *          accepts three points, but does most of the heavy-lifting when it 
 *          comes down to the ray-tracing.
 *  @author B.G. Smit
 *  @date 9/12/2020
*/

#pragma once

#include <iostream>
#include <stdint.h>
#include <cmath>
#include <cfloat>

#include "Coordinate.h"
#include "MatrixOperations.h"


class Object  {
	public:
        // Ctor and Dtor
        /**
         * @brief Constructs a new Object for each triangle
         * 
         */
		Object();
        /**
         * @brief Construct a new Object with the help of three individual
         *          points
         * 
         * @param point1 of the triangle
         * @param point2 of the triangle
         * @param point3 of the triangle
         */
        Object(const Coordinate& point1, const Coordinate& point2, 
                const Coordinate& point3);
        /**
         * @brief Construct a new Object with the help of a vector
         * 
         * @param points the vector of Coordinates
         */
        Object(std::vector<Coordinate> points);

        // Getters
        /**
         * @brief Get the points that make up the triangle
         * 
         * @return std::vector<Coordinate> the Coordinates that make up the 
         *          Triangle
         */
        std::vector<Coordinate> get_points();
        /**
         * @brief Get the normal of the triangle 
         * 
         * @return Coordinate returns a Coordinate with the normal of the object
         *          which can be used in different calculations
         */
        Coordinate get_normal();
        /**
         * @brief Get the plane created by the three points in the triangle
         * 
         * @return std::vector<double> the individual a,b,c, and k values that
         *          make the plane
         */
        std::vector<double> get_plane();

        // Setters
        /**
         * @brief Adds three individual Coordinates to the Object to create a
         *          point in 3D space
         * 
         * @param point1 of the triangle
         * @param point2 of the triangle
         * @param point3 of the triangle
         */
        void add_triangle(const Coordinate& point1, const Coordinate& point2, 
                            const Coordinate& point3);
        /**
         * @brief Adds the points that create the triangle via the help of a 
         *          vector that contains the points in 3D space
         * 
         * @param points the vector of coordinates
         */
        void add_triangle(std::vector<Coordinate> points);

        // Others
        /**
         * @brief calculates the normal of the object. It's automatically called
         *          after object creation
         * 
         */
        void calculate_object_normal();
        /**
         * @brief calculates the plane formed by the Triangle. It's 
         *          automatically called after object creation
         * 
         */
        void calculate_vector_plane();
        
	private:
        //bool is_triangle;
        Coordinate m_object_normal;                 // The normal coordinate

        std::vector<Coordinate> m_list_coordinates; // The coordinates of the triangle

        static const uint8_t MAX_REQUIRED_COORDINATES; // 3 for Triangle
};