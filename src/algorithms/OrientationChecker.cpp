#include "algorithms/OrientationChecker.hpp"

#include <iostream>

namespace SIRR {

OrientationChecker::OrientationChecker() {}

int OrientationChecker::check(std::vector<Point> const& points) const {
    float orientation(0.f);

    for (unsigned i(0); i < points.size(); ++i) {
        Point const current(points[i]);
        Point const next(points[(i+1) % points.size()]);
        orientation += (next.get_x() + current.get_x()) * (next.get_y() - current.get_y());
    }

    return orientation < 0 ? -1 : (orientation > 0 ? 1 : 0);
}

}
