#include "primitives/Point.hpp"

namespace SIRR {

Point::Point(float x, float y, float z):
    x_(x),
    y_(y),
    z_(z) {}

float Point::get_x() const {
    return x_;
}

float Point::get_y() const {
    return y_;
}

float Point::get_z() const {
    return z_;
}

void Point::set_x(float x) {
    x_ = x;
}

void Point::set_y(float y) {
    y_ = y;
}

void Point::set_z(float z) {
    z_ = z;
}

void Point::print(std::ostream& os) const {
    os << x_ << " " << y_ << " " << z_;
}

}

std::ostream& operator<< (std::ostream& os, SIRR::Point const& point) {
    point.print(os);
    return os;
}