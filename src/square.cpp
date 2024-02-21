#include "square.hpp"

Square::Square(Point center, std::string name, int side)
    : Rectangle(center, std::move(name), side, side) {
}

Square* Square::clone() const {
    return new Square(*this);
}
