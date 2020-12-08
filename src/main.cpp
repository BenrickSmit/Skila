#include <iostream>

#include "TestingClass.h"

int main(int argc, char** argv){
    TestingClass input(5);

    std::cout << "Saluton Mundo!" << std::endl;
    std::cout << "Input Number 5: " << input.get_value() << std::endl;
    return 0;
}