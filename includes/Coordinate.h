/** @brief Dummy class used for illustration purposes. Doing something with it.

    Detailed description follows here.
    For more examples of doxygen comments, look here [https://www.doxygen.nl/manual/docblocks.html] and
    [https://flcwiki.desy.de/How%20to%20document%20your%20code%20using%20doxygen]
    
    @author X. XYZ, DESY
    @date March 2008

*/

#pragma once

#include <vector>
#include <inttypes.h>
#include <iostream>

class Coordinate  {
	public:
		// Constructors and Destructors
		Coordinate();

		Coordinate(double x, double y, double z);
		Coordinate(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha);
		Coordinate(double x, double y, double z, 
					uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha);

		Coordinate(std::vector<double> input_coordinates);
		Coordinate(std::vector<uint16_t> input_colours);
		Coordinate(std::vector<double> input_coordinates, std::vector<uint16_t> input_colours);

		~Coordinate();

		// Getters
			double get_x();
			double get_y();
			double get_z();

			uint16_t get_r();
			uint16_t get_g();
			uint16_t get_b();
			uint16_t get_a();

			std::vector<double> get_coordinate();
			std::vector<uint16_t> get_colour();

		// Setters
			void set_x(double value);
			void set_y(double value);
			void set_z(double value);

			void set_r(uint16_t value);
			void set_g(uint16_t value);
			void set_b(uint16_t value);
			void set_a(uint16_t value);

			bool set_coordinate(std::vector<double> coordinate_input);
			bool set_colour(std::vector<uint16_t> colour_input);
			bool set_coordinate(double x = 0, double y = 0, double z = 0);
			bool set_colour(uint16_t red = 0, uint16_t green = 0, uint16_t blue = 0, uint16_t alpha = 0);
			
	protected:


	private:
		// Individual Coordinates
		double m_x;		// The coordinate on the x-axis
		double m_y;		// The coordinate on the y-axis
		double m_z;		// The coordinate on the z-axis

		uint16_t m_r;	// The value of red in RGBA
		uint16_t m_g;	// The value of green in RGBA
		uint16_t m_b;	// The value of blue in RGBA
		uint16_t m_a;	// The value of alpha in RGBA

};