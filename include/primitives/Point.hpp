#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>
#include <vector>

#include "utils/debug.hpp"

namespace SIRR {

template <unsigned dim>

class Point {
    public:
        Point(std::vector<float> const& coords = std::vector<float>(dim)):
            coords_() {
                if (coords.size() != dim)
                    WARNING("Point cannot be constructed from given data.\
                            Number of values doesn't match the point's\
                            dimension!");
                else coords_ = coords;
            }

        float get(unsigned i) const {
            if (i < dim)
                return coords_[i];
            WARNING("Point index out of range. Returning default value!");
            return 0.f;
        }

        void set(unsigned i, float value) {
            if (i < dim)
                coords_[i] = value;
            else WARNING("Point index out of range. Setting nothing!");
        }

        void print(std::ostream& os) const {
            for (auto coord : coords_)
                os << coord << " ";
        }

        bool operator==(Point<dim> const& rhs) const {
            for (unsigned i(0); i < dim; ++i) {
                if (coords_[i] != rhs.coords_[i])
                    return false;
            }

            return true;
        }

        Point<dim> const operator+(Point<dim> const& rhs) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] + rhs.coords_[i];
            return Point<dim>(new_coords);
        }

        Point<dim> const operator-(Point<dim> const& rhs) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] - rhs.coords_[i];
            return Point<dim>(new_coords);
        }

        Point<dim> const operator*(Point<dim> const& rhs) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] * rhs.coords_[i];
            return Point<dim>(new_coords);
        }

        Point<dim> const operator/(Point<dim> const& rhs) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] / rhs.coords_[i];
            return Point<dim>(new_coords);
        }

    private:
        std::vector<float> coords_;
};

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::Point<dim> const& point) {
    point.print(os);
    return os;
}

#endif //POINT_HPP

