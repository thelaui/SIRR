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


