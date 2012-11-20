#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

namespace SIRR {

class Point {
    public:
        Point(float x = 0.f, float y = 0.f, float z = 0.f);

        float get_x() const;
        float get_y() const;
        float get_z() const;

        void set_x(float x);
        void set_y(float y);
        void set_z(float z);

        void print(std::ostream& os) const;

        bool operator==(Point const& rhs) const;

    private:
        float x_, y_, z_;
};

bool COMPARE_X(Point const& lhs, Point const& rhs);
bool COMPARE_Y(Point const& lhs, Point const& rhs);

}

std::ostream& operator<< (std::ostream& os, SIRR::Point const& point);

#endif //POINT_HPP
