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
		/**
		 * @brief Construct a new Coordinate object for later use
		 * 
		 */
		Coordinate();

		/**
		 * @brief Construct a new Coordinate object that takes three double
		 * 			to construct a point in 3D space with a default colour
		 * 
		 * @param x the location of the point on the x-axis
		 * @param y the location of the point on the y-axis
		 * @param z the location of the point on the z-axis
		 */
		Coordinate(double x, double y, double z);
		/**
		 * @brief Construct a new Coordinate object that creates a default point
		 * 			in space, but with a specified colour
		 * 
		 * @param red the amount of red in the colour (0-255)
		 * @param green the amount of green in the colour (0-255)
		 * @param blue the amount of blue in the colour (0-255)
		 * @param alpha the transparency of the colour (0-255)
		 */
		Coordinate(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha);
		/**
		 * @brief Construct a new Coordinate object in 3D space with a specified
		 * 			colour.
		 * 
		 * @param x the location of the point on the x-axis
		 * @param y the location of the point on the y-axis
		 * @param z the location of the point on the z-axis
		 * @param red the amount of red in the colour (0-255)
		 * @param green the amount of green in the colour (0-255)
		 * @param blue the amount of blue in the colour (0-255)
		 * @param alpha the transparency of the colour (0-255)
		 */
		Coordinate(double x, double y, double z, 
					uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha);

		/**
		 * @brief Construct a new Coordinate object with the help of a location
		 * 			vector.
		 * 
		 * @param input_coordinates the vector containing the coordinates, must
		 * 			only contain 3 values (x,y,z)
		 */
		Coordinate(std::vector<double> input_coordinates);
		/**
		 * @brief Construct a new Coordinate object with the help of a colour
		 * 			vector.
		 * 
		 * @param input_colours the vector containing the colour values, must
		 * 			only contain four values (R,G,B,A)
		 */
		Coordinate(std::vector<uint16_t> input_colours);
		/**
		 * @brief Construct a new Coordinate object with the help of a location
		 * 			and colour vector.
		 * 
		 * @param input_coordinates the vetor containing the location values
		 * @param input_colours the vector containing the colour vaules
		 */
		Coordinate(std::vector<double> input_coordinates, std::vector<uint16_t> input_colours);

		// Getters
			/**
			 * @brief Get the value of x on the x-axis
			 * 
			 * @return double 
			 */
			double get_x() const;
			/**
			 * @brief Get the value of y on the y-axis
			 * 
			 * @return double 
			 */
			double get_y() const;
			/**
			 * @brief Get the value of z on the z-axis
			 * 
			 * @return double 
			 */
			double get_z() const;
			/**
			 * @brief Get the value of k, often used for plane calculations
			 * 
			 * @return double 
			 */
			double get_k() const;

			/**
			 * @brief Get the amount of red in the colour - out of 0 and 255
			 * 
			 * @return uint16_t 
			 */
			uint16_t get_r() const;
			/**
			 * @brief Get the amount of green in the colour - out of 0 and 255
			 * 
			 * @return uint16_t 
			 */
			uint16_t get_g() const;
			/**
			 * @brief Get the amount of blue in the colour - out of 0 and 255
			 * 
			 * @return uint16_t 
			 */
			uint16_t get_b() const;
			/**
			 * @brief Get the opacity of the colour
			 * 
			 * @return uint16_t 
			 */
			uint16_t get_a() const;

			/**
			 * @brief Return a vector which contains the x,y,z coordinates
			 * 
			 * @return std::vector<double> 
			 */
			std::vector<double> get_coordinate() const;
			/**
			 * @brief Return a vector that contains the plane. It returns x,y,z
			 * 			and k. It's used in certain calculations
			 * 
			 * @return std::vector<double> 
			 */
			std::vector<double> get_plane() const;
			/**
			 * @brief Returns a vector which contains the RGBA values of the
			 * 			colour
			 * 
			 * @return std::vector<uint16_t> 
			 */
			std::vector<uint16_t> get_colour() const;

			/**
			 * @brief a simple function that determines whether a coordinate
			 * 			should be considered for certain ray tracing funtions
			 * 
			 * @return true means should be considered
			 * @return false means should not be considered
			 */
			bool is_valid() const;

		// Setters
			/**
			 * @brief Set value of x on the x-axis
			 * 
			 * @param value 
			 */
			void set_x(double value);
			/**
			 * @brief Set value of y on the y-axis
			 * 
			 * @param value 
			 */
			void set_y(double value);
			/**
			 * @brief Set value of z on the z-axis
			 * 
			 * @param value 
			 */
			void set_z(double value);
			/**
			 * @brief Set the value of k for the plane
			 * 
			 * @param value 
			 */
			void set_k(double value);

			/**
			 * @brief Set the amount of red in the colour (0-255)
			 * 
			 * @param value 
			 */
			void set_r(uint16_t value);
			/**
			 * @brief Set the amount of green in the colour (0-255)
			 * 
			 * @param value 
			 */
			void set_g(uint16_t value);
			/**
			 * @brief Set the amount of blue in the colour (0-255)
			 * 
			 * @param value 
			 */
			void set_b(uint16_t value);
			/**
			 * @brief Set the opacity of the colour
			 * 
			 * @param value 
			 */
			void set_a(uint16_t value);

			/**
			 * @brief Set the coordinate with the help of a vector
			 * 
			 * @param coordinate_input the x,y,z points required
			 * @return true if the coordinate was set successfully
			 * @return false if there was some error setting the coordinate
			 */
			bool set_coordinate(std::vector<double> coordinate_input);
			/**
			 * @brief Set the colour with the help of a vector
			 * 
			 * @param colour_input the RGBA values required to set the colour
			 * @return true if the colour was set successfully
			 * @return false if there was some error setting the colour
			 */
			bool set_colour(std::vector<uint16_t> colour_input);
			/**
			 * @brief Set the plane with the help of a vector
			 * 
			 * @param plane_input the x,y,z,k values for the plane
			 * @return true if the plane was set successfully
			 * @return false if there was some error setting the plane
			 */
			bool set_plane(std::vector<double> plane_input);
			/**
			 * @brief Set the coordinate with three individual double values
			 * 
			 * @param x the x value on the x-axis
			 * @param y the y value on the y-axis
			 * @param z the z value on the z-axis
			 * @return true if the coordinate was set successfully
			 * @return false if there was some error setting the coordinate
			 */
			bool set_coordinate(double x = 0, double y = 0, double z = 0);
			/**
			 * @brief Set the colour with four individual values
			 * 
			 * @param red how much red should be in the colour (0-255)
			 * @param green how much green should be in the colour (0-255)
			 * @param blue how much blue should be in the colour (0-255)
			 * @param alpha the opacity of the colour
			 * @return true if the colour was set successfully
			 * @return false if there was an error setting the colour
			 */
			bool set_colour(uint16_t red = 0, uint16_t green = 0, uint16_t blue = 0, uint16_t alpha = 0);
			/**
			 * @brief Set the plane with four individual values
			 * 
			 * @param x the value that times x on the x-axis
			 * @param y the value that times y on the y-axis
			 * @param z the value that times z on the z-axis
			 * @param k the resulting value at the end of the equation
			 * @return true if the plane was set successfully
			 * @return false if there was some error in setting the plane
			 */
			bool set_plane(double x, double y, double z, double k);

			/**
			 * @brief Sets whether a coordinate is valid of certain calculations
			 * 
			 * @param con 
			 */
			void set_valid(bool con = true);

		// Other
			/**
			 * @brief Enables the scalar multiplication on Coordinates/Vectors
			 * 
			 * @param scalar_multiplication the value by which to multiply
			 * @return Coordinate& the resulting value after the multiplication
			 */
			Coordinate& scalar_multiply(double scalar_multiplication);
			/**
			 * @brief Overloaded equality operator
			 * 
			 * @param rhs the value on the Right Hand Side of the equation
			 * @return true if the same
			 * @return false if not the same
			 */
			bool operator==(const Coordinate &rhs) const;
			/**
			 * @brief Overloaded inequality operator
			 * 
			 * @param rhs the value on the Right Hand Side of the equation
			 * @return true if the same
			 * @return false if not the same
			 */
			bool operator!=(const Coordinate &rhs) const;
			/**
			 * @brief Overloaded subtraction
			 * 
			 * @param rhs the value on the Righ Hand Side of the equation
			 * @return Coordinate the Coordinate that results after subtracting
			 */
			Coordinate operator-(const Coordinate & rhs);
			/**
			 * @brief Overloaded addition
			 * 
			 * @param rhs the value on the Right Hand Side of the equation
			 * @return Coordinate the Coordinate that results after addition
			 */
			Coordinate operator+(const Coordinate & rhs);

			/**
			 * @brief A simple function that returns the member data as a string
			 * 
			 * @return std::string 
			 */
			std::string to_string() const;
			/**
			 * @brief A function that returns only integer values for the 
			 * 			Coordinates in the point. It rounds up to the nearest
			 * 			integer.
			 * 
			 * @return Coordinate 
			 */
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

		static const uint16_t MAX_COLOUR_VALUE;	//255
		static const uint16_t MIN_COLOUR_VALUE;	//0
};