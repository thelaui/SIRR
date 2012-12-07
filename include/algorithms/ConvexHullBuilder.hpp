#ifndef CONVEX_HULL_BUILDER_HPP
#define CONVEX_HULL_BUILDER_HPP

#include "primitives/Polygon.hpp"

#include <vector>

namespace SIRR {

class ConvexHullBuilder {
    public:
        ConvexHullBuilder();

        Polygon const build_hull(Polygon const& polygon) const;

    private:
        std::list<Point3D> const build_half_hull(std::vector<Point3D> const& sorted_points, int orientation) const;

};

}

#endif //CONVEX_HULL_BUILDER_HPP


