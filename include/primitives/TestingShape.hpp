#ifndef TESTING_SHAPE_HPP
#define TESTING_SHAPE_HPP

namespace SIRR {

template <unsigned dim>

class TestingShape {
    public:
        TestingShape() {}

        virtual ~TestingShape() {}

        virtual bool contains(Point<dim> const& point) const = 0;

        virtual bool intersects(TestingShape<dim>* shape) const = 0;

        virtual void print(std::ostream& os) const = 0;
};

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::TestingShape<dim> const& shape) {
    shape.print(os);
    return os;
}

#endif //TESTING_SHAPE_HPP



