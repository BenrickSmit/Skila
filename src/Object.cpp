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
    m_object_normal = Object::cross_product(line1, line2);
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
Coordinate Object::cross_product(const Coordinate& lhs, const Coordinate& rhs) {
    // This function will be responsible for calculating the cross product of two
    // vectors
    Coordinate result;

    // Calculate the cross-product
    result.set_x((lhs.get_y() * rhs.get_z()) - (lhs.get_z() * rhs.get_y()));
    result.set_y((lhs.get_z() * rhs.get_x()) - (lhs.get_x() * rhs.get_z()));
    result.set_z((lhs.get_x() * rhs.get_y()) - (lhs.get_y() * rhs.get_x()));

    return result;
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



double Object::get_ray_lambda(Coordinate& input_plane, 
                                    Coordinate& ray_origin,
                                    Coordinate& view_plane) {
    double lambda_to_return = 0.0;

    // The intersection of the ray (lambda) is calculated by using the input plane's x,y,z
    // values, the origin of the ray, and the view plane. 
    lambda_to_return = (dot_product(input_plane,ray_origin) + input_plane.get_k())
        / dot_product(input_plane,view_plane);

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
        to_return = Coordinate(std::vector<double>{__DBL_MIN__, __DBL_MIN__, __DBL_MIN__}); 
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
    if (within_bounding_box(to_return, m_list_coordinates)) {
        to_return = Coordinate(std::vector<double>{__DBL_MIN__, __DBL_MIN__, __DBL_MIN__}); 
        return to_return;
    }

    return to_return;
}

bool Object::within_plane(Coordinate& input_ray_intersection, 
                            std::vector<Coordinate> list_coordinates){
    // This funciton will simply determine whether the input_plane and the lines
    // found will be on the same side. If it isn't the information should not be taken to heart
    Coordinate line_t2_t3, line_t1_t3, line_t1_t2;
    double c_t2_t3, c_t1_t3, c_t1_t2;
    bool result = true;

    // Calculate the 
    line_t2_t3 = Coordinate(list_coordinates.at(1)) - Coordinate(list_coordinates.at(2));
    

    // Calculat the
    line_t1_t3 = Coordinate(list_coordinates.at(0)) - Coordinate(list_coordinates.at(2));


    // Calculate the 
    line_t1_t2 = Coordinate(list_coordinates.at(0)) - Coordinate(list_coordinates.at(1));

    return result;
}

bool Object::within_bounding_box(Coordinate& input_ray_intersection, std::vector<Coordinate> list_coordinates) {
    // This function will obtain the minimum and maximum values for the inherent
    // coordinates and determine whether the input plane is at least within the
    // bounding box of the triangle
    double min_x = 0, min_y = 0, min_z = 0, max_x = 0, max_y = 0, max_z = 0;
    bool result = true;

    // Find the minimum values
    min_x = get_min_value(list_coordinates.at(0).get_x(), list_coordinates.at(1).get_x(), list_coordinates.at(2).get_x());
    min_y = get_min_value(list_coordinates.at(0).get_y(), list_coordinates.at(1).get_y(), list_coordinates.at(2).get_y());
    min_z = get_min_value(list_coordinates.at(0).get_z(), list_coordinates.at(1).get_z(), list_coordinates.at(2).get_z());

    // Find the maximum values
    max_x = get_max_value(list_coordinates.at(0).get_x(), list_coordinates.at(1).get_x(), list_coordinates.at(2).get_x());
    max_y = get_max_value(list_coordinates.at(0).get_y(), list_coordinates.at(1).get_y(), list_coordinates.at(2).get_y());
    max_z = get_max_value(list_coordinates.at(0).get_z(), list_coordinates.at(1).get_z(), list_coordinates.at(2).get_z());

    // Determine whether the plane is within the bounding box
    // Within bounds for x
    if ((min_x > input_ray_intersection.get_x()) || (max_x < input_ray_intersection.get_x())) {
        result = false;
        return result;
    }

    // Within bounds for y
    if ((min_y > input_ray_intersection.get_y()) || (max_y < input_ray_intersection.get_y())) {
        result = false;
        return result;
    }

    // Within bounds for z
    if ((min_z > input_ray_intersection.get_z()) || (max_z < input_ray_intersection.get_z())) {
        result = false;
        return result;
    }

    return result;
}

// Tested
double Object::get_max_value(double x, double y, double z) {
    // This function simply tests each value against the next to find the maximum
    double max = __DBL_MIN__;

    // Determine which is bigger, x or y
    max = x;    
    if(max < y) {
        max = y;
    }

    // Determine which is bigger, x,y, or z
    if(max < z) {
        max = z;
    }

    return max;
}

// Tested
double Object::get_min_value(double x, double y, double z) {
    // This function simply tests each value against the next to find the minimum
    double min = __DBL_MAX__;

    // Determine which is bigger, x or y
    min = x;    
    if(min > y) {
        min = y;
    }

    // Determine which is bigger, x,y, or z
    if(min > z) {
        min = z;
    }

    return min;
}

