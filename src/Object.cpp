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

    return to_return;
}

bool Object::min(const Coordinate& to_check, const Coordinate& min_bounds) const{
    // This function determines whether the coordinate specified is within bounds of
    // all three coordinates provided by the triangle, by specifically checking to
    // see whether the coordinate to check is >= to min_bounds for each axis.
    bool result = true;

    // See if the coordinate is within bounds
    if (to_check.get_x() < min_bounds.get_x()){
        result = false;
        return result;
    }

    if (to_check.get_y() < min_bounds.get_y()) {
        result = false;
        return result;
    }

    if (to_check.get_z() < min_bounds.get_z()) {
        result = false;
        return result;
    }

    return result;
}

bool Object::max(const Coordinate& to_check, const Coordinate& max_bounds) const{
    // This function determines whether the coordinate specified is within bounds of
    // all three coordinates provided by the triangle, by specifically checking to
    // see whether the coordinate to check is <= to max_bounds for each axis.
    bool result = true;

    // See if the coordinate is within bounds
    if (to_check.get_x() >= max_bounds.get_x()){
        result = false;
        return result;
    }

    if (to_check.get_y() >= max_bounds.get_y()) {
        result = false;
        return result;
    }

    if (to_check.get_z() >= max_bounds.get_z()) {
        result = false;
        return result;
    }

    return result;   
}

Coordinate& Object::get_max_coordinate() {
    // This function will only look at the values within the
    // vector and find the max coordinates for each x,y, and z axes.
    static Coordinate max;

    // Obtain the coordinates as necessary only if equal to the required amount
    if(m_list_coordinates.size() != MAX_REQUIRED_COORDINATES) {
        std::cerr << "ERROR: Object::get_min_coordinate() total coordinates exceed " 
                    << MAX_REQUIRED_COORDINATES << std::endl;
        exit(1);
    }    

    // Check the coordinates and obtain the one with the minimum values for each coordinate
    max.set_x(get_max_value(m_list_coordinates.at(0).get_x(), m_list_coordinates.at(1).get_x(), m_list_coordinates.at(2).get_x()));
    max.set_y(get_max_value(m_list_coordinates.at(0).get_y(), m_list_coordinates.at(1).get_y(), m_list_coordinates.at(2).get_y()));
    max.set_z(get_max_value(m_list_coordinates.at(0).get_z(), m_list_coordinates.at(1).get_z(), m_list_coordinates.at(2).get_z()));
    max.set_k(get_max_value(m_list_coordinates.at(0).get_k(), m_list_coordinates.at(1).get_k(), m_list_coordinates.at(2).get_k()));

    return max;
}

Coordinate& Object::get_min_coordinate() {
    // This function will only look at the values within the
    // vector and find the min coordinates for each x,y, and z axes.
    static Coordinate min;

    // Obtain the coordinates as necessary only if equal to the required amount
    if(m_list_coordinates.size() != MAX_REQUIRED_COORDINATES) {
        std::cerr << "ERROR: Object::get_min_coordinate() total coordinates exceed " 
                    << MAX_REQUIRED_COORDINATES << std::endl;
        exit(1);
    }    

    // Check the coordinates and obtain the one with the minimum values for each coordinate
    min.set_x(get_min_value(m_list_coordinates.at(0).get_x(), m_list_coordinates.at(1).get_x(), m_list_coordinates.at(2).get_x()));
    min.set_y(get_min_value(m_list_coordinates.at(0).get_y(), m_list_coordinates.at(1).get_y(), m_list_coordinates.at(2).get_y()));
    min.set_z(get_min_value(m_list_coordinates.at(0).get_z(), m_list_coordinates.at(1).get_z(), m_list_coordinates.at(2).get_z()));
    min.set_k(get_min_value(m_list_coordinates.at(0).get_k(), m_list_coordinates.at(1).get_k(), m_list_coordinates.at(2).get_k()));

    return min;
}

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

