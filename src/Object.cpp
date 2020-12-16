#include "Object.h"  

Object::Object(){
    // Do nothing
    m_list_coordinates.clear();
}

// Tested
std::vector<Coordinate> Object::get_points() {
    // Returns the points as a vector in the order they were added
    std::vector<Coordinate> result;

    result.push_back(m_list_coordinates.at(0));
    result.push_back(m_list_coordinates.at(1));
    result.push_back(m_list_coordinates.at(2));

    return result;
}

// Tested
Coordinate Object::get_normal() {
    return m_object_normal;
}

// Tested
std::vector<double> Object::get_plane() {
    // This function will return the values stored in the normal after the addition
    // of the triangle
    std::vector<double> to_return;
    to_return.clear();

    to_return.push_back(m_object_normal.get_x());
    to_return.push_back(m_object_normal.get_y());
    to_return.push_back(m_object_normal.get_z());
    to_return.push_back(m_object_normal.get_k());

    return to_return;
}

// Tested - Indirectly
void Object::add_triangle(const Coordinate& point1, const Coordinate& point2, 
                            const Coordinate& point3) {
    // Add in the points to the vector
    m_list_coordinates.clear();
    m_list_coordinates.push_back(point1);
    m_list_coordinates.push_back(point2);
    m_list_coordinates.push_back(point3);

    // Calculate the Normals automatically
    calculate_object_normal();
    calculate_vector_plane();
}

// Tested
void Object::add_triangle(std::vector<Coordinate> points) {
    // Use the point-based overloaded add_triangle function only if the required number of points are available
    if(points.size() == 3){
        add_triangle(points.at(0),points.at(1),points.at(2));
    }else {
        std::cerr << "ERROR: Object::add_triangle() input vector size mismatch. Required: 3, Recieved: " << points.size() << std::endl;
    }
    
}

// Tested
void Object::calculate_object_normal() {
    // This funciton will use the cross-product to create the new normal coordinate for the object
    Coordinate line1, line2;

    // Obtain the lines to use for the cross product
    //line1 = m_list_coordinates.at(1) - m_list_coordinates.at(0);
    // \bug: Can't seem to properly overload functions with gtest
    line1.set_x(m_list_coordinates.at(1).get_x() - m_list_coordinates.at(0).get_x());
    line1.set_y(m_list_coordinates.at(1).get_y() - m_list_coordinates.at(0).get_y());
    line1.set_z(m_list_coordinates.at(1).get_z() - m_list_coordinates.at(0).get_z());
    line1.set_k(m_list_coordinates.at(1).get_k() - m_list_coordinates.at(0).get_k());

    //line2 = m_list_coordinates.at(2) - m_list_coordinates.at(0);
    // \bug: Can't seem to properly overload functions with gtest
    line2.set_x(m_list_coordinates.at(2).get_x() - m_list_coordinates.at(0).get_x());
    line2.set_y(m_list_coordinates.at(2).get_y() - m_list_coordinates.at(0).get_y());
    line2.set_z(m_list_coordinates.at(2).get_z() - m_list_coordinates.at(0).get_z());
    line2.set_k(m_list_coordinates.at(2).get_k() - m_list_coordinates.at(0).get_k());


    // Calculate the Cross Product, i.e. line1.x * line2.x, etc
    m_object_normal = Coordinate{0,0,0};
    m_object_normal.set_x((line1.get_y() * line2.get_z()) - (line1.get_z() * line2.get_y())); 
    m_object_normal.set_y((line1.get_z() * line2.get_x()) - (line1.get_x() * line2.get_z()));
    m_object_normal.set_z((line1.get_x() * line2.get_y()) - (line1.get_y() * line2.get_x()));
    m_object_normal.set_k(0);
}

// Tested
void Object::calculate_vector_plane() {
    // Ensure the Calculation of the Normal
    calculate_object_normal();

    // Proceed to calculate K for use
    Coordinate temp = m_list_coordinates.at(0);
    Coordinate tempNormal = m_object_normal;

    // Set the value of k
    m_object_normal.set_k(dot_product(tempNormal.scalar_multiply(-1), temp));
}

// Tested
double Object::dot_product(Coordinate& lhs, Coordinate& rhs) {
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