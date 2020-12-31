/** @brief The Coordinate class is the primary class used in the project. It
 * 			contains data such as the coordinate location, it's colour, as well
 * 			as it's alpha value.
 *  @author B.G. Smit
 *  @date 9/12/2020
*/

#pragma once

#include <cmath>
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

		// Getters
			double get_x() const;
			double get_y() const;
			double get_z() const;
			double get_k() const;

			uint16_t get_r() const;
			uint16_t get_g() const;
			uint16_t get_b() const;
			uint16_t get_a() const;

			std::vector<double> get_coordinate() const;
			std::vector<double> get_plane() const;
			std::vector<uint16_t> get_colour() const;

			bool is_valid() const;

		// Setters
			void set_x(double value);
			void set_y(double value);
			void set_z(double value);
			void set_k(double value);

			void set_r(uint16_t value);
			void set_g(uint16_t value);
			void set_b(uint16_t value);
			void set_a(uint16_t value);

			bool set_coordinate(std::vector<double> coordinate_input);
			bool set_colour(std::vector<uint16_t> colour_input);
			bool set_plane(std::vector<double> plane_input);
			bool set_coordinate(double x = 0, double y = 0, double z = 0);
			bool set_colour(uint16_t red = 0, uint16_t green = 0, uint16_t blue = 0, uint16_t alpha = 0);
			bool set_plane(double x, double y, double z, double k);

			void set_valid(bool con = true);

		// Other
			Coordinate& scalar_multiply(double scalar_multiplication);
			bool operator==(const Coordinate &rhs) const;
			bool operator!=(const Coordinate &rhs) const;
			Coordinate operator-(const Coordinate & rhs);
			Coordinate operator+(const Coordinate & rhs);

			std::string to_string() const;
			Coordinate get_rounded() const;
	protected:


	private:
		// Individual Coordinates
		double m_x;		// The coordinate on the x-axis
		double m_y;		// The coordinate on the y-axis
		double m_z;		// The coordinate on the z-axis
		double m_k;		// The coordinate used for a plane

		uint16_t m_r;	// The value of red in RGBA
		uint16_t m_g;	// The value of green in RGBA
		uint16_t m_b;	// The value of blue in RGBA
		uint16_t m_a;	// The value of alpha in RGBA

		bool m_is_valid;	// Sets up whether the vector is valid or not

		static const uint16_t MAX_COLOUR_VALUE;
		static const uint16_t MIN_COLOUR_VALUE;
};