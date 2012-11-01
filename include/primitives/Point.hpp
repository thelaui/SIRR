#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

namespace SIRR {

class Point {
    public:
        Point(float x, float y, float z);

        float get_x() const;
        float get_y() const;
        float get_z() const;

        void set_x(float x);
        void set_y(float y);
        void set_z(float z);

        void print(std::ostream& os) const;

    private:
        float x_, y_, z_;
};

}

std::ostream& operator<< (std::ostream& os, SIRR::Point const& point);

#endif //POINT_HPP
