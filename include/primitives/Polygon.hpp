#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "primitives/Point.hpp"

#include <list>

namespace SIRR {

class Polygon {
    public:
        Polygon();

        std::list<Point> const& get_points() const;

        void add_point(Point const& point);

        void print(std::ostream& os) const;


    private:
        std::list<Point> points_;
};

}

std::ostream& operator<< (std::ostream& os, SIRR::Polygon const& ploygon);

#endif //POLYGON_HPP

