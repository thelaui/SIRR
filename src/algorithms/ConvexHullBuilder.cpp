#include "algorithms/ConvexHullBuilder.hpp"
#include "algorithms/OrientationChecker.hpp"

#include <vector>
#include <iostream>

namespace SIRR {

ConvexHullBuilder::ConvexHullBuilder() {}

Polygon const ConvexHullBuilder::build_hull(Polygon const& polygon) const{
    if (polygon.get_points().size() < 3)
        return polygon;

    std::list<Point3D> tmp(polygon.get_points());
    tmp.sort(COMPARE_X);

    std::list<Point3D> hull(build_half_hull(std::vector<Point3D>(tmp.begin(), tmp.end()), -1));
    std::list<Point3D> lower_hull(build_half_hull(std::vector<Point3D>(tmp.rbegin(), tmp.rend()), -1));

    hull.insert(hull.end(), ++lower_hull.begin(), --lower_hull.end());
    return Polygon(hull);
}

std::list<Point3D> const ConvexHullBuilder::build_half_hull(std::vector<Point3D> const& sorted_points, int orientation) const {
    std::list<Point3D> result;
    result.push_back(sorted_points[0]);
    result.push_back(sorted_points[1]);

    OrientationChecker o_checker;
    for (unsigned i(2); i < sorted_points.size(); ++i) {
        result.push_back(sorted_points[i]);
        while (result.size() > 2 &&
                o_checker.check({*(--(--(--result.end()))), *(--(--result.end())), result.back()}) != orientation) {
            result.erase(--(--result.end()));
        }
    }

    return result;
}

}

