#include "Object.h"  

const uint8_t Object::MAX_REQUIRED_COORDINATES = 3;

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
    if(points.size() == MAX_REQUIRED_COORDINATES){
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
    //m_object_normal.set_x((line1.get_y() * line2.get_z()) - (line1.get_z() * line2.get_y())); 
    //m_object_normal.set_y((line1.get_z() * line2.get_x()) - (line1.get_x() * line2.get_z()));
    //m_object_normal.set_z((line1.get_x() * line2.get_y()) - (line1.get_y() * line2.get_x()));
    m_object_normal = MatrixOperations::cross_product(line1, line2);
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
    m_object_normal.set_k(MatrixOperations::dot_product(tempNormal.scalar_multiply(-1), temp));
}


double Object::get_ray_lambda(Coordinate& input_plane, 
                                    Coordinate& ray_origin,
                                    Coordinate& view_plane) {
    double lambda_to_return = 0.0;

    // The intersection of the ray (lambda) is calculated by using the input plane's x,y,z
    // values, the origin of the ray, and the view plane. 
    lambda_to_return = (MatrixOperations::dot_product(input_plane,ray_origin) + input_plane.get_k())
        / MatrixOperations::dot_product(input_plane,view_plane);

    return lambda_to_return;
}

Coordinate Object::get_ray_intersection(Coordinate& input_plane,
                                                Coordinate& ray_origin,
                                                Coordinate& view_plane) {
    Coordinate to_return;

    // Get the value of lambda to calculate the coordinate of intersection between
    // the ray from the view_plane to the object itself
    double lambda = get_ray_lambda(input_plane, ray_origin, view_plane);

    if(lambda < 0){
        // IN the case that lambda is negative, it means that the intersection
        // point is behind the camera, and thus not necessary
        to_return = Coordinate(std::vector<double>{FLT_MIN, FLT_MIN, FLT_MIN}); 
        return to_return;
    }

    to_return.set_x((lambda*view_plane.get_x()) + ray_origin.get_x());
    to_return.set_y((lambda*view_plane.get_y()) + ray_origin.get_y());
    to_return.set_z((lambda*view_plane.get_z()) + ray_origin.get_z());
    to_return.set_k(0);

    // Set the colour of the plane based on the point used.
    // This can be used in the future to help with refraction and reflection,
    // even transparent materials
    // \todo: add in colour transparency, reflection, refraction, etc.
    to_return.set_r(input_plane.get_r());
    to_return.set_g(input_plane.get_g());
    to_return.set_b(input_plane.get_b());
    to_return.set_a(input_plane.get_a());

    // Determine whether the ray is at least within the bounding box for sanity and validity
    if (!MatrixOperations::within_bounding_box(to_return, m_list_coordinates)) {
        to_return = Coordinate(std::vector<double>{FLT_MIN, FLT_MIN, FLT_MIN}); 
        return to_return;
    }

    // Do something with the actual ray and the intersection

    return to_return;
}


