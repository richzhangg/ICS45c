#include "shape.hpp"
#include <iostream>

Shape::Shape(Point center, std::string name) : center(center), name(std::move(name)) {}

void Shape::print(std::ostream& out) const {
    out << name << "(" << center.x << ", " << center.y << ")" << std::endl;
}

