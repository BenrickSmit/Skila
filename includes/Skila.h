/** @brief Skila is the main class behind the functionality of the ray tracer.
 *          It contains all the functions needed to create simple and elegant 
 *          ray traced graphics.
 *  @author B.G. Smit
 *   @date 9/12/2020
*/

//Skila: Icelandic for Render

#pragma once

#include <vector>
#include <cstdint>

#include "Coordinate.h"
#include "Object.h"

class Skila  {

	public:
        /**
         * @brief Construct a new default Skila object
         * 
         */
		Skila();
        /**
         * @brief Construct a new Skila object with the help of provided 
         *          coordinates
         * 
         * @param camera_origin the location of the camera 
         * @param viewport the location of the viewport
         */
        Skila(Coordinate& camera_origin, Coordinate& viewport);
        /**
         * @brief Construct a new Skila object with the help of provided
         *          coordinates and viewport size
         * 
         * @param camera_origin the location of the camera
         * @param viewport the location of the viewport
         * @param width the width of the viewport (in pixels)
         * @param height the height of the viewport (in pixels)
         */
        Skila(Coordinate& camera_origin, Coordinate& viewport, 
                                uint16_t width, uint16_t height);

        // Getters
        /**
         * @brief Get the camera location as a Coordinate
         * 
         * @return Coordinate location of the camera
         */
        Coordinate& get_camera();
        /**
         * @brief Get the viewport "coordinates" as a coordinate
         * 
         * @return Coordinate 
         */
        Coordinate& get_viewport();
        /**
         * @brief Get the size of the viewport as a vector.
         * 
         * @return std::vector<uint16_t> width first, height second
         */
        std::vector<uint16_t> get_size();

        // Setters
        /**
         * @brief Set the camera location with the help of an input Coordinate
         * 
         * @param camera_origin location in x,y,z
         */
        void set_camera(Coordinate& camera_origin);
        /**
         * @brief Set the viewport location with the help of a Coordinate
         * 
         * @param viewport 
         */
        void set_viewport(Coordinate& viewport);
        /**
         * @brief Set the size the viewport so as to enable traversal with rays
         * 
         * @param width of the window
         * @param height ofthe window
         */
        void set_size(uint16_t width, uint16_t height);

        // Others
        /**
         * @brief default method of adding objects to the scene
         * 
         * @param obj the object to add to the scene
         */
        void add_object(Object obj);
        /**
         * @brief adds a pyramid to the scene at the provided location
         * 
         * @param start_location the middle of the base of the pyramid
         * @param size the length of one line in the object
         */
        void add_pyramid(Coordinate start_location, double size = 1);

        // Scene functions
        /**
         * @brief This function removes all objects in the scene
         * 
         */
        void clear_scene();
        /**
         * @brief Get the objects in the scene as a vector
         * 
         * @return std::vector<Object>& a reference vector of all objects that make up 
         *          the current scene
         */
        std::vector<Object>& get_objects();


    protected:
        /**
         * @brief This function will use some of the information to set up
         *          all hte necessities for rendering of the final image
         * 
         */
        void init();

    private:
        Coordinate m_camera;
        Coordinate m_viewport;
        uint16_t m_width, m_height;
        std::vector<Object> m_scene_objects;

        static const double PIXEL_CONSTANT;
};