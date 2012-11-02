#ifndef ORIENTATION_CHECKER_HPP
#define ORIENTATION_CHECKER_HPP

#include "primitives/Point.hpp"

#include <vector>

namespace SIRR {

class OrientationChecker {
    public:
        OrientationChecker();

        // CCW = 1, COLL = 0, CW = -1
        int check(std::vector<Point> const& points) const;

};

}

#endif //ORIENTATION_CHECKER_HPP



