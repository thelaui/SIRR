#include "SIRR.hpp"

#include <iostream>
#include <vector>

int main(int argc, const char** argv) {

    SIRR::Line l1(SIRR::Point(1.f, 1.f, 0.f), SIRR::Point(7.f, 7.f, 0.f));
    SIRR::Line l2(SIRR::Point(1.f, 7.f, 0.f), SIRR::Point(7.f, 1.f, 0.f));
    SIRR::Line l3(SIRR::Point(2.f, 3.f, 0.f), SIRR::Point(2.f, 7.f, 0.f));
//    SIRR::Line l4(SIRR::Point(4.f, 0.f, 0.f), SIRR::Point(4.f, 7.f, 0.f));
//    SIRR::Line l5(SIRR::Point(7.f, 0.f, 0.f), SIRR::Point(7.f, 7.f, 0.f));
//    SIRR::Line l6(SIRR::Point(0.f, 0.f, 0.f), SIRR::Point(0.f, 7.f, 0.f));


    std::list<SIRR::Line> lines({l1, l2, l3});

    SIRR::LineIntersectionFinder finder;
    auto points(finder.find_intersections(lines));

    SIRR::SVGBuilder builder;
    builder.build("intersections.svg", lines, points);

    return 0;
}
