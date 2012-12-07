#ifndef POINT_2D_HPP
#define POINT_2D_HPP

#include <ostream>

#include "primitives/Point.hpp"

namespace SIRR {

class Point3D : public Point<3> {
    public:
        Point3D(float x = 0.f, float y = 0.f, float z = 0.f);

        float get_x() const;
        float get_y() const;
        float get_z() const;

        void set_x(float x);
        void set_y(float y);
        void set_z(float z);

    private:
        float x_, y_, z_;
};

bool COMPARE_X(Point3D const& lhs, Point3D const& rhs);
bool COMPARE_Y(Point3D const& lhs, Point3D const& rhs);

}

#endif //POINT_2D_HPP
