#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <vector>
#include <cmath>

namespace SIRR {

template <unsigned dim>

class Point {
    public:
        Point(std::vector<float> const& coords = std::vector<float>(dim)):
            coords_() {
                if (coords.size() != dim)
                    std::cout << "Point cannot be constructed from given data.\
                            Number of values doesn't match the point's\
                            dimension!" << std::endl;
                else coords_ = coords;
            }

        float get(unsigned i) const {
            if (i < dim)
                return coords_[i];
            std::cout << "Point index out of range. Returning default value!" << std::endl;
            return 0.f;
        }

        void set(unsigned i, float value) {
            if (i < dim)
                coords_[i] = value;
            else std::cout << "Point index out of range. Setting nothing!" << std::endl;
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

        bool operator<(Point<dim> const& rhs) const {
            for (unsigned i(0); i < dim; ++i) {
                if (coords_[i] > rhs.coords_[i])
                    return false;
            }

            return true;
        }

        bool operator>(Point<dim> const& rhs) const {
            for (unsigned i(0); i < dim; ++i) {
                if (coords_[i] < rhs.coords_[i])
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

        Point<dim> const operator+(float scalar) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] + scalar;
            return Point<dim>(new_coords);
        }

        Point<dim> const operator-(Point<dim> const& rhs) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] - rhs.coords_[i];
            return Point<dim>(new_coords);
        }

        Point<dim> const operator-(float scalar) const {
            std::vector<float> new_coords(dim);
            for (unsigned i(0); i < dim; ++i)
                new_coords[i] = coords_[i] - scalar;
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

        static Point<dim> const get_random(float min = 0.f, float max = 100.f) {
            if (!random_initialized_) {
                srand(time(NULL));
                random_initialized_ = true;
            }

            Point<dim> p;
            for (unsigned i(0); i < dim; ++i)
                p.set(i, static_cast<float>(std::rand())/RAND_MAX
                         * (max - min) + min);
            return p;
        }

    private:
        std::vector<float> coords_;

        static bool random_initialized_;
};


template <unsigned dim>
struct COMPARE_POINTS_LESS {
    COMPARE_POINTS_LESS(unsigned comp_pos):
        comp_pos_(comp_pos) {}

    bool operator()(Point<dim> const& lhs, Point<dim> const& rhs) const{
        if (lhs.get(comp_pos_) == rhs.get(comp_pos_)) {
            for (unsigned pos(0); pos < dim; ++pos) {
                if (pos != comp_pos_ && lhs.get(pos) != rhs.get(pos))
                    return lhs.get(pos) < rhs.get(pos);
            }
            return false;
        }
        else
            return lhs.get(comp_pos_) < rhs.get(comp_pos_);
    }

    unsigned comp_pos_;
};

template <unsigned dim>
float distance_squared(Point<dim> const& p1, Point<dim> const& p2) {
    Point<dim> substract(p2-p1);
    float result(0.f);
    for (unsigned i(0); i < dim; ++i)
        result += substract.get(i) * substract.get(i);
    return result;
}

template <unsigned dim>
float distance(Point<dim> const& p1, Point<dim> const& p2) {
    return std::sqrt(distance_squared(p1, p2));
}

template <unsigned dim>
bool Point<dim>::random_initialized_ = false;

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::Point<dim> const& point) {
    point.print(os);
    return os;
}

#endif //POINT_HPP

