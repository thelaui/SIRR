#ifndef SHAPE_CHECKER_HPP
#define SHAPE_CHECKER_HPP

#include "primitives/BoundingBox.hpp"
#include "primitives/HyperCircle.hpp"

namespace SIRR {

template <unsigned dim>

class ShapeChecker {
    public:
        ShapeChecker() {}

        bool is_inside(TestingShape<dim>* s1, TestingShape<dim>* s2) const {
            auto s1_box(dynamic_cast<BoundingBox<dim>*>(s1));
            auto s1_circle(dynamic_cast<HyperCircle<dim>*>(s1));
            auto s2_box(dynamic_cast<BoundingBox<dim>*>(s2));
            auto s2_circle(dynamic_cast<HyperCircle<dim>*>(s2));

            if (s1_box) {
                if (s2_box)
                    return s2_box->contains(s1_box->get_min()) && s2_box->contains(s1_box->get_max());
                else if (s2_circle)
                    return s2_circle->contains(s1_box->get_min()) && s2_circle->contains(s1_box->get_max());
            } else if (s1_circle) {
                if (s2_box)
                    return s2_box->contains(s1_circle->get_center()) &&
                        !(s1_circle->contains(s2_box->get_min()) || s1_circle->contains(s2_box->get_max()));
                else if (s2_circle)
                    return distance(s1_circle->get_center(), s2_circle->get_center()) + s1_circle->get_radius()
                        <= s2_circle->get_radius();;
            }

            return false;
        }

        bool intersects(TestingShape<dim>* s1, TestingShape<dim>* s2) const {
            return false;
        }
};

}


#endif //SHAPE_CHECKER_HPP




