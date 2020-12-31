#include "Skila.h"  

const double Skila::PIXEL_CONSTANT = 0.01;

Skila::Skila(){
    init();
}

Skila::Skila(Coordinate& camera_origin, Coordinate& viewport) {
    set_camera(camera_origin);
    set_viewport(viewport);
    set_size(800, 600);
}

Coordinate& Skila::get_camera() {
    return m_camera;
}

Coordinate& Skila::get_viewport() {
    return m_viewport;
}

std::vector<uint16_t> Skila::get_size() {
    // This function simply returns the height and width of the scene to render
    std::vector<uint16_t> result;

    result.clear();
    result.push_back(m_width);
    result.push_back(m_height);

    return result;
}

void Skila::set_camera(Coordinate& camera_origin) {
    // This sets the location of the camera. This is what will change when 
    // looking at different locations
    m_camera = camera_origin;
}

void Skila::set_viewport(Coordinate& viewport) {
    // What is import about the viewport is that it will be used during the ray
    // casting to determine what colour what is, as such it is important to know
    // a few constants as well
    m_viewport = viewport;
}

void Skila::set_size(uint16_t width, uint16_t height) {
    m_width = width;
    m_height = height;
}

void Skila::add_object(Object obj) {
    // Simply add the object to the scene
    // There is no need for a reference copy
    m_scene_objects.push_back(obj);
}

void Skila::add_pyramid(Coordinate start_location, double size) {
    // Create the sides of the pyramid adn add them to the list of objects in
    // the scene
    // The base is made up of two triangles
    Coordinate base11{start_location.get_x()-size/2.0, start_location.get_y()-size/2.0, 
                    start_location.get_z()};
    Coordinate base12{start_location.get_x()+size/2.0, start_location.get_y()+size/2.0, 
                    start_location.get_z()};
    Coordinate base13{start_location.get_x()-size/2.0, start_location.get_y()+size/2.0, 
                    start_location.get_z()};

    Coordinate base21{start_location.get_x()-size/2.0, start_location.get_y()-size/2.0, 
                    start_location.get_z()};
    Coordinate base22{start_location.get_x()-size/2.0, start_location.get_y()+size/2.0, 
                    start_location.get_z()};
    Coordinate base23{start_location.get_x()+size/2.0, start_location.get_y()-size/2.0, 
                    start_location.get_z()};

    Coordinate front1{base21.get_x(), base21.get_y(), base21.get_z()};
    Coordinate front2{base11.get_x(), base11.get_x(), base11.get_z()};
    Coordinate front3{start_location.get_x(), start_location.get_y(), start_location.get_z() + size};
    
    Coordinate back1{base22.get_x(), base22.get_y(), base22.get_z()};
    Coordinate back2{base12.get_x(), base12.get_y(), base12.get_z()};
    Coordinate back3{start_location.get_x(), start_location.get_y(), start_location.get_z() + size};
    
    Coordinate left1{base11.get_x(), base11.get_y(), base11.get_z()};
    Coordinate left2{base13.get_x(), base13.get_y(), base13.get_z()};
    Coordinate left3{start_location.get_x(), start_location.get_y(), start_location.get_z()+size};
    
    Coordinate right1{base21.get_x(), base21.get_y(), base21.get_z()};
    Coordinate right2{base23.get_x(), base23.get_y(), base23.get_z()};
    Coordinate right3{start_location.get_x(), start_location.get_y(), start_location.get_z()+size};

    // Create the objects to add
    Object base1, base2, front, back, left, right;
    // The base
    base1.add_triangle(base11, base12, base13);
    base2.add_triangle(base21, base22, base23);
    base1.set_colour(255,0,0,255);
    base2.set_colour(255,0,0,255);
    // The front
    front.add_triangle(front1, front2, front3);
    front.set_colour(255,0,0,255);
    // the back
    back.add_triangle(back1, back2, back3);
    back.set_colour(255,0,0,255);
    // the left
    left.add_triangle(left1, left2, left3);
    left.set_colour(255,0,0,255);
    // the right
    right.add_triangle(right1, right2, right3);
    right.set_colour(255,0,0,255);

    // Add the objects to the scene
    add_object(base1);
    add_object(base2);
    add_object(front);
    add_object(back);
    add_object(left);
    add_object(right);
}

void Skila::clear_scene() {
    m_scene_objects.clear();
}

std::vector<Object>& Skila::get_objects() {
    return m_scene_objects;
}

void Skila::init() {
    // This function calls the defaults for the objects in question
    // Create the default coordinates
    static Coordinate default_camera_origin{0,-1,-1};
    static Coordinate default_viewport{0,0,1};

    // Set the default values
    set_camera(default_camera_origin);
    set_viewport(default_viewport);
    set_size(800,600);
}
