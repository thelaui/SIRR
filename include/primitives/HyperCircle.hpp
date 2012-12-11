#ifndef HYPER_CIRCLE_HPP
#define HYPER_CIRCLE_HPP

#include "primitives/TestingShape.hpp"
#include "primitives/Point.hpp"

namespace SIRR {

template <unsigned dim>

class HyperCircle : public TestingShape<dim> {
    public:
        HyperCircle(Point<dim> const& center, float radius):
            TestingShape<dim>(),
            center_(center),
            radius_(radius) {}

        bool contains(Point<dim> const& point) const {
            return distance_squared(center_, point) < radius_ * radius_;
        }

        bool intersects(TestingShape<dim>* shape) const {
            return false;
        }

        Point<dim> const& get_center() const {
            return center_;
        }

        float get_radius() const {
            return radius_;
        }

        void print(std::ostream& os) const {
            os << center_ << " | " << radius_;
        }

    private:
        Point<dim> center_;
        float radius_;
};

}


#endif //HYPER_CIRCLE_HPP




