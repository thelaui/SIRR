#include "primitives/Point3D.hpp"

namespace SIRR {

Point3D::Point3D(float x, float y, float z):
    Point({x, y, z}) {}

float Point3D::get_x() const {
    return get(0);
}

float Point3D::get_y() const {
    return get(1);
}

float Point3D::get_z() const {
    return get(2);
}

void Point3D::set_x(float x) {
    set(0, x);
}

void Point3D::set_y(float y) {
    set(1, y);
}

void Point3D::set_z(float z) {
    set(2, z);
}

bool COMPARE_X(Point3D const& lhs, Point3D const& rhs) {
    if (lhs.get_x() == rhs.get_x())
        return lhs.get_y() < rhs.get_y();
    return lhs.get_x() < rhs.get_x();
}

bool COMPARE_Y(Point3D const& lhs, Point3D const& rhs) {
    if (lhs.get_y() == rhs.get_y())
        return lhs.get_x() < rhs.get_x();
    return lhs.get_y() < rhs.get_y();
}

}
