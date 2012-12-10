#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "primitives/Point3D.hpp"
#include "primitives/Line3D.hpp"

#include <list>

namespace SIRR {

class Polygon {
    public:
        Polygon();
        Polygon(std::list<Point3D> const& points);

        std::list<Point3D> const& get_points() const;
        std::list<Line3D> const as_lines() const;

        void add_point(Point3D const& point);

        void print(std::ostream& os) const;


    private:
        std::list<Point3D> points_;
};

}

std::ostream& operator<< (std::ostream& os, SIRR::Polygon const& ploygon);

#endif //POLYGON_HPP

