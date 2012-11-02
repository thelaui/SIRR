#include "primitives/Polygon.hpp"

namespace SIRR {

Polygon::Polygon():
    points_() {}

Polygon::Polygon(std::list<Point> const& points):
    points_(points) {}

std::list<Point> const& Polygon::get_points() const {
    return points_;
}

void Polygon::add_point(Point const& point) {
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

