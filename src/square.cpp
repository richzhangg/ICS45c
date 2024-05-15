#include "square.hpp"

Square::Square(Point center, std::string name, int side)
    : Rectangle(center, name, side, side) {
}

Square* Square::clone() const {
    return new Square(*this);
}
