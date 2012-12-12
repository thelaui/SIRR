#ifndef TESTING_SHAPE_HPP
#define TESTING_SHAPE_HPP

#include "primitives/Line.hpp"

namespace SIRR {

template <unsigned dim>

class TestingShape {
    public:
        TestingShape() {}

        virtual ~TestingShape() {}

        virtual bool contains(Point<dim> const& point) const = 0;

        virtual std::list<Line<3>> const as_2D_lines() const = 0;

        virtual void print(std::ostream& os) const = 0;
};

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::TestingShape<dim> const& shape) {
    shape.print(os);
    return os;
}

#endif //TESTING_SHAPE_HPP



