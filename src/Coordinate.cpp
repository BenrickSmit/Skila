#include "Coordinate.h"  

//Static Variables
const uint16_t Coordinate::MAX_COLOUR_VALUE = 255;
const uint16_t Coordinate::MIN_COLOUR_VALUE = 0;

//Tested
Coordinate::Coordinate(){
    // Init the Default Coordinates to 000 and colour to 000255
    set_coordinate(0,0,0);
    set_colour(0,0,0,255);
    set_valid();
}

//Tested
Coordinate::Coordinate(double x, double y, double z){
    // Init the Default Coordinates to 000 and colour to 000255
    set_coordinate(x,y,z);
    set_colour(0,0,0,255);
    set_valid();
}

//Tested
Coordinate::Coordinate(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha){
    set_coordinate(0,0,0);
    set_colour(red, green, blue, alpha);
    set_valid();
}

//Tested
Coordinate::Coordinate(double x, double y, double z, uint16_t red, uint16_t green, 
                        uint16_t blue, uint16_t alpha){
    set_coordinate(x, y, z);
    set_colour(red, green, blue, alpha);
    set_valid();
}

//Tested
Coordinate::Coordinate(std::vector<uint16_t> input_colours){
    set_coordinate();
    set_colour(input_colours);
}

//Tested
Coordinate::Coordinate(std::vector<double> input_coordinates){
    set_coordinate(input_coordinates);
    set_colour();
}

//Tested
Coordinate::Coordinate(std::vector<double> input_coordinates, std::vector<uint16_t> input_colours){
    set_coordinate(input_coordinates);
    set_colour(input_colours);
}


//Tested - Indirectly
double Coordinate::get_x() const {
    return m_x;
}

//Tested - Indirectly
double Coordinate::get_y() const {
    return m_y;
}

//Tested - Indirectly
double Coordinate::get_z() const {
    return m_z;
}

double Coordinate::get_k() const {
    return m_k;
}

//Tested - Indirectly
uint16_t Coordinate::get_r() const {
    return m_r;
}

//Tested - Indirectly
uint16_t Coordinate::get_g() const {
    return m_g;
}

//Tested - Indirectly
uint16_t Coordinate::get_b() const {
    return m_b;
}

//Tested - Indirectly
uint16_t Coordinate::get_a() const {
    return m_a;
}

//Tested
std::vector<double> Coordinate::get_coordinate() const {
    return std::vector<double>({m_x, m_y, m_z});
}

std::vector<double> Coordinate::get_plane() const {
    return std::vector<double>({m_x, m_y, m_z, m_k});
}

//Tested
void Coordinate::set_x(double value) {
    m_x = value;
}

//Tested
void Coordinate::set_y(double value) {
    m_y = value;
}

//Tested
void Coordinate::set_z(double value) {
    m_z = value;
}

void Coordinate::set_k(double value) {
    m_k = value;
}

//Tested - indirectly
void Coordinate::set_r(uint16_t value) {
    // Sanitise colour input and ensure it stays within 0-255
    if(value <= 0){// Technically impossible due to "unsigned int" but still testable
        m_r = MIN_COLOUR_VALUE;
    }else if(value >= 255){
        m_r = MAX_COLOUR_VALUE;
    }else {
        m_r = value;
    }
}

//Tested - indirectly
void Coordinate::set_g(uint16_t value) {
    // Sanitise colour input and ensure it stays within 0-255
    if(value <= 0){// Technically impossible due to "unsigned int" but still testable
        m_g = MIN_COLOUR_VALUE;
    }else if(value >= 255){
        m_g = MAX_COLOUR_VALUE;
    }else {
        m_g = value;
    }
}

//Tested - indirectly
void Coordinate::set_b(uint16_t value) {
    // Sanitise colour input and ensure it stays within 0-255
    if(value <= 0){// Technically impossible due to "unsigned int" but still testable
        m_b = MIN_COLOUR_VALUE;
    }else if(value >= 255){
        m_b = MAX_COLOUR_VALUE;
    }else {
        m_b = value;
    }
}

//Tested - indirectly
void Coordinate::set_a(uint16_t value) {
    // Sanitise colour input and ensure it stays within 0-255
    if(value <= 0){// Technically impossible due to "unsigned int" but still testable
        m_a = MIN_COLOUR_VALUE;
    }else if(value >= 255){
        m_a = MAX_COLOUR_VALUE;
    }else {
        m_a = value;
    }
}

bool Coordinate::set_coordinate(std::vector<double> coordinate_input) {
    // A quick sanity check to ensure the vector has 3 elements
    if (coordinate_input.size() == 3){
        set_coordinate(coordinate_input.at(0),coordinate_input.at(1),coordinate_input.at(2));
        return true;
    }else {
        set_coordinate();
        std::cerr << "Coordinate::set_colour() Error: vector size mismatch" << std::endl;
        return false;
    }
}

// Tested
bool Coordinate::set_colour(std::vector<uint16_t> colour_input) {
    // A quick sanity check to ensure the vetor has 3 elements
    if (colour_input.size() == 4){
        set_colour(colour_input.at(0),colour_input.at(1),colour_input.at(2),colour_input.at(3));
        return true;
    }else {
        set_colour();
        std::cerr << "Coordinate::set_colour() Error: vector size mismatch" << std::endl;
        return false;
    }
}

//Tested
std::vector<uint16_t> Coordinate::get_colour() const {
    return std::vector<uint16_t>({m_r, m_g, m_b, m_a});
}

bool Coordinate::is_valid() const {
    return m_is_valid;
}

//Tested
bool Coordinate::set_coordinate(double x, double y, double z) {
    set_x(x);
    set_y(y);
    set_z(z);
    set_k(0);
    return true;
}

//Tested
bool Coordinate::set_colour(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha) {
    set_r(red);
    set_g(green);
    set_b(blue);
    set_a(alpha);
    return true;
}

bool Coordinate::set_plane(double x, double y, double z, double k) {
    set_x(x);
    set_y(y);
    set_z(z);
    set_k(k);
    return true;
}

bool Coordinate::set_plane(std::vector<double> plane_input) {
    if (plane_input.size() == 4){
        set_plane(plane_input.at(0),plane_input.at(1),plane_input.at(2),plane_input.at(3));
        return true;
    }else {
        set_plane(0,0,0,0);
        std::cerr << "Coordinate::set_plane() Error: vector size mismatch" << std::endl;
        return false;
    }
}

Coordinate& Coordinate::scalar_multiply(double scalar_multiplication) {
    static Coordinate result;

    // Scalar multiplication simply multiplies every member variable
    // by the scalar specified
    result.set_x(get_x() * scalar_multiplication);
    result.set_y(get_y() * scalar_multiplication);
    result.set_z(get_z() * scalar_multiplication);
    result.set_k(get_k() * scalar_multiplication);

    return result;
}

void Coordinate::set_valid(bool con) {
    m_is_valid = con;
}

bool Coordinate::operator==(const Coordinate &rhs) const{
    return ((get_x() == rhs.get_x()) && (get_y() == rhs.get_y()) && 
            (get_z() == rhs.get_z()) && (get_k() == rhs.get_k()));
}

bool Coordinate::operator!=(const Coordinate &rhs) const{
    return !(*this == rhs);
}

Coordinate Coordinate::operator-(const Coordinate & rhs) {
    Coordinate result;

    result.set_x(get_x() - rhs.get_x());
    result.set_y(get_y() - rhs.get_y());
    result.set_z(get_z() - rhs.get_z());
    result.set_k(get_k() - rhs.get_k());

    return result;
}

std::string Coordinate::to_string() const{
    std::string to_return = "";

    to_return += "x: " + std::to_string(get_x());
    to_return += ", y: " + std::to_string(get_y());
    to_return += ", z: " + std::to_string(get_z());
    to_return += ", k: " + std::to_string(get_k());
    to_return += "; \n";

    return to_return;
}

Coordinate Coordinate::operator+(const Coordinate & rhs) {
    Coordinate result;

    result.set_x(get_x() + rhs.get_x());
    result.set_y(get_y() + rhs.get_y());
    result.set_z(get_z() + rhs.get_z());
    result.set_k(get_k() + rhs.get_k());

    return result;
}

