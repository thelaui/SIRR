#include "primitives/Line.hpp"
#include "algorithms/OrientationChecker.hpp"

#include <cmath>
#include <iostream>

namespace SIRR {

Line::Line(Point3D const& a, Point3D const& b):
    a_(a),
    b_(b) {
        if (a_.get_y() > b_.get_y())
            std::swap(a_, b_);
        else if (a.get_y() == b.get_y())
            if (a.get_x() > b.get_x())
                std::swap(a_, b_);
    }

Point3D const& Line::get_a() const {
    return a_;
}

Point3D const& Line::get_b() const {
    return b_;
}

Point3D const Line::intersects(Line const& l) const {
    float x(0.f), y(0.f), z(-1.f);

    OrientationChecker checker;
//    std::cout << "Checking intersection of " << *this << " and " << l << std::endl;

    float check_1(checker.check({a_, b_, l.a_})), check_2(checker.check({a_, b_, l.b_})),
           check_3( checker.check({a_, l.a_, l.b_})), check_4(checker.check({b_, l.a_, l.b_}));

    if (check_1 * check_2 * check_3 * check_4 != 0) {

        if (check_1 != check_2 && check_3 != check_4) {

            float fract((a_.get_x() - b_.get_x()) * (l.a_.get_y() - l.b_.get_y()) - (a_.get_y() - b_.get_y()) * (l.a_.get_x() - l.b_.get_x()));

            if (std::abs(fract) != 0.f) {

                x = ((a_.get_x() * b_.get_y() - a_.get_y() * b_.get_x() )  * (l.a_.get_x() - l.b_.get_x()) -
                    (l.a_.get_x() * l.b_.get_y() - l.a_.get_y() * l.b_.get_x() )  * (a_.get_x() - b_.get_x())) /
                    fract;

                y = ((a_.get_x() * b_.get_y() - a_.get_y() * b_.get_x() )  * (l.a_.get_y() - l.b_.get_y()) -
                    (l.a_.get_x() * l.b_.get_y() - l.a_.get_y() * l.b_.get_x() )  * (a_.get_y() - b_.get_y())) /
                    fract;
                z = 0.f;

//                std::cout << "Found intersection at " << Point3D(x, y, z) << std::endl;
            }

        }
    }

    return Point3D(x, y, z);
}


void Line::print(std::ostream& os) const {
    os << a_ << " -- " << b_;
}

}

std::ostream& operator<< (std::ostream& os, SIRR::Line const& line) {
    line.print(os);
    return os;
}

