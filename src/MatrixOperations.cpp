#include "MatrixOperations.h"

const float MatrixOperations::PI = 3.14159265358979;

// Tested
double MatrixOperations::dot_product(Coordinate& lhs, Coordinate& rhs) {
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

// Tested - Indirectly in the test_object function for normals
Coordinate MatrixOperations::cross_product(Coordinate& lhs, Coordinate& rhs) {
    // This function will be responsible for calculating the cross product of two
    // vectors
    Coordinate result;

    // Calculate the cross-product
    result.set_x((lhs.get_y() * rhs.get_z()) - (lhs.get_z() * rhs.get_y()));
    result.set_y((lhs.get_z() * rhs.get_x()) - (lhs.get_x() * rhs.get_z()));
    result.set_z((lhs.get_x() * rhs.get_y()) - (lhs.get_y() * rhs.get_x()));

    return result;
}

// Tested - Indirectly
bool MatrixOperations::within_plane(Coordinate& input_ray_intersection,
    std::vector<Coordinate> list_coordinates) {
    //\todo: optimise!
    // This funciton will simply determine whether the input_plane and the lines
    // found will be on the same side. If it isn't the information should not be taken to heart
    Coordinate t1, t2, t3;
    Coordinate a, b, i, v;
    double c;
    bool result = true;

    t1 = static_cast<Coordinate&>(list_coordinates.at(0));
    t2 = static_cast<Coordinate&>(list_coordinates.at(1));
    t3 = static_cast<Coordinate&>(list_coordinates.at(2));

    // Calculate whether the intersection is on the same side as t2_t3.
    i = input_ray_intersection;
    v = subtract(t2,t3);         //v used later in the formulat
    a = cross_product(v, subtract(i, t3));
    b = cross_product(v, subtract(t1, t3));
    c = dot_product(a,b);

    if(c <= 0) {
        result = false;
        return result;
    }

    // Calculate whether the intersection is on the same side as t1_t3.
    i = input_ray_intersection;
    v = subtract(t1,t3);         //v used later in the formulat
    a = cross_product(v, subtract(i, t3));
    b = cross_product(v, subtract(t2, t3));
    c = dot_product(a,b);

    if(c <= 0) {
        result = false;
        return result;
    }

    // Calculate whether the intersection is on the same side as t1_t2.
    i = input_ray_intersection;
    v = subtract(t1,t2);         //v used later in the formulat
    a = cross_product(v, subtract(i, t2));
    b = cross_product(v, subtract(t3, t1));
    c = dot_product(a,b);

    if(c <= 0) {
        result = false;
        return result;
    }

    // Should all the tests pass return true
    result = true;
    return result;
}

// Tested - Indirectly
bool MatrixOperations::within_bounding_box(Coordinate& input_ray_intersection, std::vector<Coordinate> list_coordinates) {
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
double MatrixOperations::get_max_value(double x, double y, double z) {
    // This function simply tests each value against the next to find the maximum
    double max = FLT_MIN;

    // Determine which is bigger, x or y
    max = x;
    if (max < y) {
        max = y;
    }

    // Determine which is bigger, x,y, or z
    if (max < z) {
        max = z;
    }

    return max;
}

// Tested
Coordinate& MatrixOperations::subtract(Coordinate& lhs, Coordinate& rhs) {
    static Coordinate result;

    result.set_x(lhs.get_x() - rhs.get_x());
    result.set_y(lhs.get_y() - rhs.get_y());
    result.set_z(lhs.get_z() - rhs.get_z());
    result.set_k(lhs.get_k() - rhs.get_k());

    return result;
}

// Tested
double MatrixOperations::get_ray_lambda(Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane) {
    double lambda_to_return = -1.0;

    // The intersection of the ray (lambda) is calculated by using the input plane's x,y,z
    // values, the origin of the ray (camera), and the view plane (about 1m away from the camera).
    // the view plane uses the following formula for calculation
    // ((size_of_pixel_in_meters)*(x_pixel_position - half_total_pixels),
    // (size_of_pixel_in_meters)*(y_pixel_position - half_total_pixels), 
    // (size_of_pixel_in_meters)*(z_pixel_position - half_total_pixels))

    double numerator = -1 * (MatrixOperations::dot_product(input_plane, ray_origin) + input_plane.get_k());
    double denominator = MatrixOperations::dot_product(input_plane, view_plane);

    // A sanity check for division by 0
    if (denominator == 0) {
        lambda_to_return = -1.0;
        return lambda_to_return;
    }
    // A sanity check for 0 divided by something
    if (numerator == 0) {
        lambda_to_return = 0.0;
        return lambda_to_return;
    }

    // Calculate the actual lambda as necessary
    lambda_to_return = numerator / denominator;

    return lambda_to_return;
}

bool MatrixOperations::get_ray_intersection(Coordinate& result, Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane, std::vector<Coordinate> list_coordinates) {
    // Get the value of lambda to calculate the coordinate of intersection between
    // the ray from the view_plane to the object itself
    double lambda = get_ray_lambda(input_plane, ray_origin, view_plane);

    if(lambda < 0){
        // IN the case that lambda is negative, it means that the intersection
        // point is behind the camera, and thus not necessary
        result = Coordinate(std::vector<double>{FLT_MIN, FLT_MIN, FLT_MIN}); 
        result.set_valid(false);
        return result.is_valid();
    }

    result.set_x((lambda*view_plane.get_x()) + ray_origin.get_x());
    result.set_y((lambda*view_plane.get_y()) + ray_origin.get_y());
    result.set_z((lambda*view_plane.get_z()) + ray_origin.get_z());
    result.set_k(0);

    // Set the colour of the plane based on the point used.
    // This can be used in the future to help with refraction and reflection,
    // even transparent materials
    // \todo: add in colour transparency, reflection, refraction, etc.
    result.set_r(input_plane.get_r());
    result.set_g(input_plane.get_g());
    result.set_b(input_plane.get_b());
    result.set_a(input_plane.get_a());

    // Determine whether the ray is at least within the bounding box for sanity and validity
    // PS: A quick Sanity Check
    if (!MatrixOperations::within_bounding_box(result, list_coordinates)) {
        result = Coordinate(std::vector<double>{FLT_MIN, FLT_MIN, FLT_MIN}); 
        result.set_valid(false);
        return result.is_valid();
    }

    //std::cout << ">>>> MatrixOperations::within_bounding_box(): " << MatrixOperations::within_bounding_box(result, list_coordinates) << std::endl;

    // Determine whether the ray actually intersects the plane
    if (!MatrixOperations::within_plane(result, list_coordinates)){
        result = Coordinate(std::vector<double>{FLT_MIN, FLT_MIN, FLT_MIN});
        result.set_valid(false);
        return result.is_valid();
    }

    //std::cout << ">>>> MatrixOperations::within_plane(): " << MatrixOperations::within_plane(result, list_coordinates) << std::endl;

    // The ray is valid in all other cases, so set it as such
    result.set_valid(true);

    return result.is_valid();
}

double MatrixOperations::get_ray_rasterisation(Coordinate& ray_intersection_point, Coordinate& ray_origin) {
    // This function determines how bright the light of the pixel is by using the
    // pythagorean theorem - with some optimizations
    double result = -1;

    // Calculate the light strength
    result = std::sqrt((ray_intersection_point.get_x() - ray_origin.get_x()) * 
                        (ray_intersection_point.get_x() - ray_origin.get_x()) + 
                        (ray_intersection_point.get_y() - ray_origin.get_y()) * 
                        (ray_intersection_point.get_y() - ray_origin.get_y()) + 
                        (ray_intersection_point.get_z() - ray_origin.get_z()) * 
                        (ray_intersection_point.get_z() - ray_origin.get_z()));

    //Convert the result to a value out of 100
    return (1/result);
}

// Tested
Coordinate& MatrixOperations::rotate_x(Coordinate& input, double angle) {
    // Making sure bigger angles can be used
    if (angle > 360){
        angle = std::fmod(angle, 360.0);
    }

    static Coordinate result;

    result.set_x(round((input.get_x() * std::cos(to_radians(angle))) - (input.get_y() * std::sin(to_radians(angle)))));
    result.set_y(round((input.get_x() * std::sin(to_radians(angle))) + (input.get_y()*std::cos(to_radians(angle)))));
    result.set_z(round(input.get_z()));

    return result;
}

// Tested
Coordinate& MatrixOperations::rotate_y(Coordinate& input, double angle) {
    // Making sure bigger angles can be used
    if (angle > 360){
        angle = std::fmod(angle, 360.0);
    }

    static Coordinate result;

    result.set_x(round((input.get_x() * std::cos(to_radians(angle))) + (input.get_z() * std::sin(to_radians(angle)))));
    result.set_y(round(input.get_y()));
    result.set_z(round((-1* input.get_x() * std::sin(to_radians(angle))) + (input.get_z() * std::cos(to_radians(angle)))));

    return result;
}

// Tested
Coordinate& MatrixOperations::rotate_z(Coordinate& input, double angle) {
    // Making sure bigger angles can be used
    if (angle > 360){
        angle = std::fmod(angle, 360.0);
    }

    static Coordinate result;

    result.set_x(round((input.get_x() * std::cos(to_radians(angle))) - (input.get_y() * std::sin(to_radians(angle)))));
    result.set_y(round((input.get_x() * std::sin(to_radians(angle))) + (input.get_y() * std::cos(to_radians(angle)))));
    result.set_z(round(input.get_z()));

    return result;
}

// Tested
std::vector<uint16_t> MatrixOperations::get_ray_colour(Coordinate& input, double ray_rasterisation) {
    // This function will take the colour it gets from the input coordinate and 
    // the value of the colour based on how far it is from the light source, etc
    std::vector<uint16_t> colour_return;

    uint16_t r = input.get_colour().at(0);
    uint16_t g = input.get_colour().at(1);
    uint16_t b = input.get_colour().at(2);
    // alpha will not be affected by rays

    colour_return.clear();
    colour_return.push_back(r);
    colour_return.push_back(g);
    colour_return.push_back(b);
    colour_return.push_back(input.get_colour().at(3));

    return colour_return;
}

// Tested
double MatrixOperations::round(double input, int decimals) {
    int decimal_factor = 1;

    // Depending on the number of decimals times decimals by ten
    for(auto i = 0; i < decimals; i++){
        decimal_factor *= 10;
    }

    return floor(input*decimal_factor+0.5)/decimal_factor;
}

// Tested - Indirectly
double MatrixOperations::to_radians(double input_angle) {
    // This function takes in a degree value, and returns the value in radians,
    // since c++'s internal std::cos(), std::sin(), etc, use radians rather than
    // degrees
    return (input_angle * PI/180.0);
}

// Tested
double MatrixOperations::get_min_value(double x, double y, double z) {
    // This function simply tests each value against the next to find the minimum
    double min = FLT_MAX;

    // Determine which is bigger, x or y
    min = x;
    if (min > y) {
        min = y;
    }

    // Determine which is bigger, x,y, or z
    if (min > z) {
        min = z;
    }

    return min;
}