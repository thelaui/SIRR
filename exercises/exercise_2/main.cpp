#include "SIRR.hpp"

#include <iostream>
#include <vector>

int main(int argc, const char** argv) {

    SIRR::Line l1(SIRR::Point(1.1f, 1.4f, 0.f), SIRR::Point(7.5f, 6.8f, 0.f));
    SIRR::Line l2(SIRR::Point(1.2f, 7.1f, 0.f), SIRR::Point(7.4f, 1.3f, 0.f));
//    SIRR::Line l3(SIRR::Point(2.f, 0.f, 0.f), SIRR::Point(2.f, 7.f, 0.f));
//    SIRR::Line l4(SIRR::Point(4.f, 0.f, 0.f), SIRR::Point(4.f, 7.f, 0.f));
//    SIRR::Line l5(SIRR::Point(7.f, 0.f, 0.f), SIRR::Point(7.f, 7.f, 0.f));
//    SIRR::Line l6(SIRR::Point(0.f, 0.f, 0.f), SIRR::Point(0.f, 7.f, 0.f));

    std::list<SIRR::Line> lines({l1, l2});//, l3, l4, l5, l6});

    SIRR::SVGBuilder builder;
    builder.build("raw.svg", lines, {});
//
//
//    SIRR::StatusStructure status_structure;
//    status_structure.add_line(&l1);
//    status_structure.add_line(&l2);
//    status_structure.add_line(&l5);
//    status_structure.add_line(&l4);
//    status_structure.add_line(&l6);
//    status_structure.add_line(&l3);
//
//    std::cout << status_structure << std::endl;
//
//    status_structure.remove_line(&l6);
//
//    std::cout << status_structure << std::endl;
//
//    status_structure.swap(&l4, &l3);
//
//    std::cout << status_structure << std::endl;

    SIRR::LineIntersectionFinder finder;
    auto points(finder.find_intersections(lines));

    builder.build("intersections.svg", lines, points);

    return 0;
}
