#include "primitives/Line.hpp"
#include "algorithms/OrientationChecker.hpp"

#include <cmath>
#include <iostream>

namespace SIRR {

Line::Line(Point const& a, Point const& b):
    a_(a),
    b_(b) {
        if (a_.get_y() > b_.get_y())
            std::swap(a_, b_);
    }

Point const& Line::get_a() const {
    return a_;
}

Point const& Line::get_b() const {
    return b_;
}

Point const Line::intersects(Line const& l) const {
    float x(0.f), y(0.f), z(-1.f);

    OrientationChecker checker;

    if (checker.check({a_, b_, l.a_}) != checker.check({a_, b_, l.b_}) &&
        checker.check({a_, l.a_, l.b_}) != checker.check({b_, l.a_, l.b_})) {

        float fract((a_.get_x() - b_.get_x()) * (l.a_.get_y() - l.b_.get_y()) - (a_.get_y() - b_.get_y()) * (l.a_.get_x() - l.b_.get_x()));

        if (std::abs(fract) != 0.f) {

            x = ((a_.get_x() * b_.get_y() - a_.get_y() * b_.get_x() )  * (l.a_.get_x() - l.b_.get_x()) -
                (l.a_.get_x() * l.b_.get_y() - l.a_.get_y() * l.b_.get_x() )  * (a_.get_x() - b_.get_x())) /
                fract;

            y = ((a_.get_x() * b_.get_y() - a_.get_y() * b_.get_x() )  * (l.a_.get_y() - l.b_.get_y()) -
                (l.a_.get_x() * l.b_.get_y() - l.a_.get_y() * l.b_.get_x() )  * (a_.get_y() - b_.get_y())) /
                fract;
            z = 0.f;
        }

    }

    return Point(x, y, z);
}


void Line::print(std::ostream& os) const {
    os << a_ << " -- " << b_;
}

}

std::ostream& operator<< (std::ostream& os, SIRR::Line const& line) {
    line.print(os);
    return os;
}

