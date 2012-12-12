#ifndef HYPER_CIRCLE_HPP
#define HYPER_CIRCLE_HPP

#include "primitives/TestingShape.hpp"

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

        Point<dim> const& get_center() const {
            return center_;
        }

        float get_radius() const {
            return radius_;
        }

        std::list<Line<3>> const as_2D_lines() const {
            std::list<Line<3>> lines;
            unsigned res(100);

            Point<3> last({center_.get(0) + radius_, center_.get(1), 0});

            for (unsigned i(1); i <= res; ++i) {

                Point<3> last_transformed({last.get(0) - center_.get(0),
                                           last.get(1) - center_.get(1),
                                           0});

                float const angle(2*M_PI * float(i)/ float(res));
                float const sin(std::sin(angle));
                float const cos(std::cos(angle));

                Point<3> current({radius_ * cos + center_.get(0),
                                  radius_ * sin + center_.get(1),
                                  0});

                lines.push_back(Line<3>(last, current));
                last = current;
            }

            return lines;
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




