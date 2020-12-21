/** @brief Dummy class used for illustration purposes. Doing something with it.

    Detailed description follows here.
    For more examples of doxygen comments, look here [https://www.doxygen.nl/manual/docblocks.html] and
    [https://flcwiki.desy.de/How%20to%20document%20your%20code%20using%20doxygen]
    
    @author X. XYZ, DESY
    @date March 2008

*/

#pragma once

#include <iostream>
#include <stdint.h>
#include <cmath>

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
        double get_ray_lambda(Coordinate& input_plane, 
                                    Coordinate& ray_origin,
                                    Coordinate& view_plane);
        Coordinate get_ray_intersection(Coordinate& input_plane,
                                                Coordinate& ray_origin,
                                                Coordinate& view_plane);
	private:
        //bool is_triangle;
        Coordinate m_object_normal;

        std::vector<Coordinate> m_list_coordinates;

        static const uint8_t MAX_REQUIRED_COORDINATES;
};