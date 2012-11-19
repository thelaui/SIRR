#ifndef LINE_INTERSECTION_FINDER_HPP
#define LINE_INTERSECTION_FINDER_HPP

#include <list>

#include "primitives/Line.hpp"

namespace SIRR {

class LineIntersectionFinder {
    public:
        LineIntersectionFinder();

        std::list<Point> const find_intersections(std::list<Line>& lines) const;
};

}

#endif //LINE_INTERSECTION_FINDER_HPP




