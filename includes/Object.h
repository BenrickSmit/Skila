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
		Object();

        // Getters
        std::vector<Coordinate> get_points();
        Coordinate get_normal();
        std::vector<double> get_plane();

        // Setters
        void add_triangle(const Coordinate& point1, const Coordinate& point2, 
                            const Coordinate& point3);
        void add_triangle(std::vector<Coordinate> points);

        // Others
        void calculate_object_normal();
        void calculate_vector_plane();
        
	private:
        //bool is_triangle;
        Coordinate m_object_normal;

        std::vector<Coordinate> m_list_coordinates;

        static const uint8_t MAX_REQUIRED_COORDINATES;
};