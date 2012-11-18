#ifndef LINE_HPP
#define LINE_HPP

#include <ostream>

#include "primitives/Point.hpp"

namespace SIRR {

class Line {
    public:
        Line(Point const& a, Point const& b);

        Point const& get_a() const;
        Point const& get_b() const;

        Point const intersects(Line const& l) const;

        void print(std::ostream& os) const;

    private:
        Point a_, b_;
};


}

std::ostream& operator<< (std::ostream& os, SIRR::Line const& line);

#endif //LINE_HPP

