#include "shape.hpp"
#include <iostream>
using namespace std;

Shape::Shape(Point center, string name) {
    this->center = center;
    this->name = name;
}

void Shape::print(ostream& out) const {
    out << name << " at (" << center.x << ", " << center.y << ") area = " << this->area() << endl;
}
