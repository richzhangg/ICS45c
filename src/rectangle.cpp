#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(Point center, std::string name, int width, int height)
    : Shape(center, std::move(name)), width(width), height(height) {}

double Rectangle::area() const {
    return width * height;
}

void Rectangle::draw(std::ostream& out) const {
    for (int i = 0; i < height; i += 2) {
        for (int j = 0; j < width; ++j) {
            out << '*';
        }
        out << '\n';
    }
}

Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
}
