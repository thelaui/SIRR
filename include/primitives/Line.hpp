#ifndef LINE_HPP
#define LINE_HPP

#include <ostream>

#include "primitives/Point3D.hpp"

namespace SIRR {

class Line {
    public:
        Line(Point3D const& a, Point3D const& b);

        Point3D const& get_a() const;
        Point3D const& get_b() const;

        Point3D const intersects(Line const& l) const;

        void print(std::ostream& os) const;

    private:
        Point3D a_, b_;
};


}

std::ostream& operator<< (std::ostream& os, SIRR::Line const& line);

#endif //LINE_HPP

