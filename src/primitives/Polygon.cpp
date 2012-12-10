#include "primitives/Polygon.hpp"

namespace SIRR {

Polygon::Polygon():
    points_() {}

Polygon::Polygon(std::list<Point3D> const& points):
    points_(points) {}

std::list<Point3D> const& Polygon::get_points() const {
    return points_;
}

std::list<Line3D> const Polygon::as_lines() const {
    std::list<Line3D> lines;

    auto last_point(points_.begin());
    auto current_point(++points_.begin());

    while (current_point != points_.end()) {
        lines.push_back(Line3D(*last_point, *current_point));
        last_point = current_point;
        ++current_point;
    }

    return lines;
}

void Polygon::add_point(Point3D const& point) {
    points_.push_back(point);
}

void Polygon::print(std::ostream& os) const {
    for (auto point : points_) {
        point.print(os);
        os << std::endl;
    }
}

}

std::ostream& operator<< (std::ostream& os, SIRR::Polygon const& polygon) {
    polygon.print(os);
    return os;
}

