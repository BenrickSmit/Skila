#include "Coordinate.h"  

Coordinate::Coordinate(){
    // Init the Default Coordinates to 000 and colour to 0000
    set_coordinate(0,0,0);
    set_colour(0,0,0,0);
}

Coordinate::Coordinate(double x, double y, double z){
    set_coordinate(x,y,z);
    set_colour(0,0,0,0);
}

Coordinate::Coordinate(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha){
    set_coordinate(0,0,0);
    set_colour(red, green, blue, alpha);
}

Coordinate::Coordinate(double x, double y, double z, uint16_t red, uint16_t green, 
                        uint16_t blue, uint16_t alpha){
    set_coordinate(x, y, z);
    set_colour(red, green, blue);
}

Coordinate::Coordinate(std::vector<uint16_t> input_colours){
    set_coordinate();
    set_colour(input_colours);
}

Coordinate::Coordinate(std::vector<double> input_coordinates){
    set_coordinate(input_coordinates);
    set_colour();
}

Coordinate::Coordinate(std::vector<double> input_coordinates, std::vector<uint16_t> input_colours){
    set_coordinate(input_coordinates);
    set_colour(input_colours);
}

Coordinate::~Coordinate(){

}

double Coordinate::get_x() {
    return m_x;
}

double Coordinate::get_y() {
    return m_y;
}

double Coordinate::get_z() {
    return m_z;
}

uint16_t Coordinate::get_r() {
    return m_r;
}

uint16_t Coordinate::get_g() {
    return m_g;
}

uint16_t Coordinate::get_b() {
    return m_b;
}

uint16_t Coordinate::get_a() {
    return m_a;
}

std::vector<double> Coordinate::get_coordinate() {
    return std::vector<double>(m_x, m_y, m_z);
}

void Coordinate::set_x(double value) {
    m_x = value;
}

void Coordinate::set_y(double value) {
    m_y = value;
}

void Coordinate::set_z(double value) {
    m_z = value;
}

void Coordinate::set_r(uint16_t value) {
    m_r = value;
}

void Coordinate::set_g(uint16_t value) {
    m_g = value;
}

void Coordinate::set_b(uint16_t value) {
    m_b = value;
}

void Coordinate::set_a(uint16_t value) {
    m_a = value;
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

std::vector<uint16_t> Coordinate::get_colour() {
    return std::vector<uint16_t>(m_r, m_g, m_b, m_a);
}

bool Coordinate::set_coordinate(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
    return true;
}

bool Coordinate::set_colour(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha) {
    m_r = red;
    m_g = green;
    m_b = blue;
    m_a = alpha;
    return true;
}