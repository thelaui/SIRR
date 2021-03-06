#ifndef LINE_INTERSECTION_FINDER_HPP
#define LINE_INTERSECTION_FINDER_HPP

#include <list>

#include "primitives/Line3D.hpp"

namespace SIRR {

class LineIntersectionFinder {
    public:
        LineIntersectionFinder();

        std::list<Point3D> const find_intersections(std::list<Line3D>& lines) const;
};

}

#endif //LINE_INTERSECTION_FINDER_HPP




