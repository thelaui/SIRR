#ifndef LINE_HPP
#define LINE_HPP

#include <ostream>

#include "primitives/Point.hpp"

namespace SIRR {

template <unsigned dim>
class Line {
    public:
        Line(Point<dim> const& a, Point<dim> const& b):
            a_(a),
            b_(b) {}

        Point<dim> const& get_a() const {
            return a_;
        }

        Point<dim> const& get_b() const {
            return b_;
        }

        void print(std::ostream& os) const {
            os << a_ << " - " << b_;
        }

    private:
        Point<dim> a_, b_;
};


}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::Line<dim> const& line) {
    line.print(os);
    return os;
}

#endif //LINE_HPP


