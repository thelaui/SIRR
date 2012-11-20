#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "primitives/Point.hpp"
#include "primitives/Line.hpp"

#include <list>

namespace SIRR {

class Polygon {
    public:
        Polygon();
        Polygon(std::list<Point> const& points);

        std::list<Point> const& get_points() const;
        std::list<Line> const as_lines() const;

        void add_point(Point const& point);

        void print(std::ostream& os) const;


    private:
        std::list<Point> points_;
};

}

std::ostream& operator<< (std::ostream& os, SIRR::Polygon const& ploygon);

#endif //POLYGON_HPP

