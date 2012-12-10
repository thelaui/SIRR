#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <cfloat>
#include <set>

#include "primitives/Line.hpp"
#include "utils/debug.hpp"

namespace SIRR {

template <unsigned dim>

class BoundingBox {
    public:
        BoundingBox(std::list<Point<dim>> const& points = std::list<Point<dim>>()):
            min_(std::vector<float>(dim, FLT_MAX)),
            max_() {

                for (auto point : points)
                    include(point);
            }

        BoundingBox(std::vector<Point<dim>> const& points):
            min_(std::vector<float>(dim, FLT_MAX)),
            max_() {

                for (auto point : points)
                    include(point);
            }


        void include(Point<dim> const& point) {

            for (unsigned i(0); i < dim; ++i) {
                if (point.get(i) < min_.get(i)) {
                    min_.set(i, point.get(i));
                }

                if (point.get(i) > max_.get(i)) {
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
            std::list<Point<dim>> points({min_, max_, box.min_, box.max_});
            BoundingBox<dim> closure(points);
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

        std::list<Line<3>> const as_2D_lines() const {
            std::list<Line<3>> lines;
            lines.push_back(Line<3>(min_, Point<3>({max_.get(0), min_.get(1), 0})));
            lines.push_back(Line<3>(min_, Point<3>({min_.get(0), max_.get(1), 0})));
            lines.push_back(Line<3>(max_, Point<3>({max_.get(0), min_.get(1), 0})));
            lines.push_back(Line<3>(max_, Point<3>({min_.get(0), max_.get(1), 0})));

            return lines;
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


