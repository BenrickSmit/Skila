#include "MatrixOperations.h"

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

bool MatrixOperations::within_plane(Coordinate& input_ray_intersection,
    std::vector<Coordinate> list_coordinates) {
    // This funciton will simply determine whether the input_plane and the lines
    // found will be on the same side. If it isn't the information should not be taken to heart
    Coordinate line_t2_t3, line_t1_t3, line_t1_t2;
    Coordinate t1, t2, t3;
    Coordinate a, b;
    double c_t2_t3, c_t1_t3, c_t1_t2;
    bool result = true;

    t1 = static_cast<Coordinate&>(list_coordinates.at(0));
    t2 = static_cast<Coordinate&>(list_coordinates.at(1));
    t3 = static_cast<Coordinate&>(list_coordinates.at(2));

    // Calculate whether the intersection is within/on the triangle
    line_t2_t3 = t2 - t3;
    a = cross_product(line_t2_t3, subtract(input_ray_intersection, t3));
    b = cross_product(line_t2_t3, subtract(t1, t3));
    c_t2_t3 = dot_product(a,b);

    if (c_t2_t3 <= 0){
        result = false;
        return result;
    }

    // Calculat the
    line_t1_t3 = t1 - t3;
    a = cross_product(line_t1_t3, subtract(input_ray_intersection, t3));
    b = cross_product(line_t1_t3, subtract(t2, t3));
    c_t1_t3 = dot_product(a,b);

    if (c_t1_t3 <= 0){
        result = false;
        return result;
    }

    // Calculate the 
    line_t1_t2 = t1 - t2;
    a = cross_product(line_t1_t2, subtract(input_ray_intersection, t2));
    b = cross_product(line_t1_t2, subtract(t3, t2));
    c_t1_t2 = dot_product(a,b);

    if (c_t1_t2 <= 0){
        result = false;
        return result;
    }

    return result;
}

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

double MatrixOperations::get_ray_lambda(Coordinate& input_plane, Coordinate& ray_origin, Coordinate& view_plane) {
    double lambda_to_return = 0.0;

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

    std::cout << ">> input_plane.k:          " << input_plane.get_k() << std::endl;
    std::cout << ">> input_plane.ray_origin: " << MatrixOperations::dot_product(input_plane,ray_origin) << std::endl;
    std::cout << ">> input_plane.view_plane: " << MatrixOperations::dot_product(input_plane, view_plane) << std::endl;

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

    // Determine whether the ray actually intersects the plane
    if (!MatrixOperations::within_plane(result, list_coordinates)){
        result = Coordinate(std::vector<double>{FLT_MIN, FLT_MIN, FLT_MIN});
        result.set_valid(false);
        return result.is_valid();
    }

    // The ray is valid in all other cases, so set it as such
    result.set_valid(true);

    // Do something with the actual ray and the intersection

    return result.is_valid();
}

// Most Important - find arbitrary function for matrix rotation
Coordinate& MatrixOperations::rotate_x(Coordinate& input, double angle) {
    // Making sure bigger angles can be used
    if (angle > 360){
        angle = std::fmod(angle, 360.0);
    }

    static Coordinate result;

    result.set_x(round((input.get_x() * std::cos(angle)) - (input.get_y() * std::sin(angle))));
    result.set_y(round((input.get_x() * std::sin(angle)) + (input.get_y()*std::cos(angle))));
    result.set_z(round(input.get_z()));

    return result;
}

Coordinate& MatrixOperations::rotate_y(Coordinate& input, double angle) {
    // Making sure bigger angles can be used
    if (angle > 360){
        angle = std::fmod(angle, 360.0);
    }

    static Coordinate result;

    result.set_x(round((input.get_x() * std::cos(angle)) + (input.get_z() * std::sin(angle))));
    result.set_y(round(input.get_y()));
    result.set_z(round((-1* input.get_x() * std::sin(angle)) + (input.get_z() * std::cos(angle))));

    return result;
}

Coordinate& MatrixOperations::rotate_z(Coordinate& input, double angle) {
    // Making sure bigger angles can be used
    if (angle > 360){
        angle = std::fmod(angle, 360.0);
    }

    static Coordinate result;

    result.set_x(round((input.get_x() * std::cos(angle)) + (input.get_z() * std::sin(angle))));
    result.set_y(round(input.get_y()));
    result.set_z(round((-1* input.get_x() * std::sin(angle)) + (input.get_z() * std::cos(angle))));

    return result;
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