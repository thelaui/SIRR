#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <cfloat>

#include "primitives/Point.hpp"
#include "utils/debug.hpp"

namespace SIRR {

template <unsigned dim>

class BoundingBox {
    public:
        BoundingBox(std::list<Point<dim>> const& points):
            min_(std::vector<float>(dim, FLT_MAX)),
            max_() {

                for (auto point : points)
                    include(point);
            }

        void include(Point<dim> const& point) {

            for (unsigned i(0); i < dim; ++i) {
                if (point.get(i) < min_.get(i)) {
                    min_.set(i, point.get(i));
                } else if (point.get(i) > max_.get(i)) {
                    max_.set(i, point.get(i));
                }
            }
        }

        bool contains(Point<dim> const& point) const {

            for (unsigned i(0); i < dim; ++i) {
                if (point.get(i) < min_.get(i) || point.get(i) > max_.get(i))
                    return false;
            }

            return true;
        }

        bool is_inside(BoundingBox<dim> const& box) const {
            return box.contains(min_) && box.contains(max_);
        }

        bool intersects(BoundingBox<dim> const& box) const {
            BoundingBox closure({min_, max_, box.min_, box.max_});
            for (unsigned i(0); i < dim; ++i) {
                if ((max_.get(i) - min_.get(i)) +
                    (box.max_.get(i) - box.min_.get(i)) <
                    (closure.max_.get(i) - closure.min_.get(i)))
                    return false;
            }

            return true;
        }

        Point<dim> const& get_min() const {
            return min_;
        }

        Point<dim> const& get_max() const {
            return max_;
        }

        void print(std::ostream& os) const {
            os << min_ << " -- " << max_;
        }

    private:
        Point<dim> min_, max_;
};

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::BoundingBox<dim> const& box) {
    box.print(os);
    return os;
}

#endif //BOUNDING_BOX_HPP


