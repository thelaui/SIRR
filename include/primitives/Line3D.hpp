#ifndef LINE_3D_HPP
#define LINE_3D_HPP

#include <ostream>

#include "primitives/Point3D.hpp"

namespace SIRR {

class Line3D {
    public:
        Line3D(Point3D const& a, Point3D const& b);

        Point3D const& get_a() const;
        Point3D const& get_b() const;

        Point3D const intersects(Line3D const& l) const;

        void print(std::ostream& os) const;

    private:
        Point3D a_, b_;
};


}

std::ostream& operator<< (std::ostream& os, SIRR::Line3D const& line);

#endif //LINE_3D_HPP

