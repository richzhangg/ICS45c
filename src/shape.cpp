#include "shape.hpp"
#include <iostream>

// Implement the constructor
Shape::Shape(Point center, std::string name) : center(center), name(std::move(name)) {}

// Implement the print function
void Shape::print(std::ostream& out) const {
    out << name << "(" << center.x << ", " << center.y << ")" << std::endl;
}

