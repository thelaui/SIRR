#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

//    SIRR::Line l1(SIRR::Point(0.f, 0.f, 0.f), SIRR::Point(4.f, 0.f, 0.f));
//    SIRR::Line l2(SIRR::Point(4.f, 0.f, 0.f), SIRR::Point(4.f, 4.f, 0.f));
//    SIRR::Line l3(SIRR::Point(3.f, 1.f, 0.f), SIRR::Point(3.f, 7.f, 0.f));
//    SIRR::Line l4(SIRR::Point(1.f, 4.f, 0.f), SIRR::Point(7.f, 3.f, 0.f));
//    SIRR::Line l5(SIRR::Point(7.f, 0.f, 0.f), SIRR::Point(7.f, 7.f, 0.f));
//    SIRR::Line l6(SIRR::Point(0.f, 0.f, 0.f), SIRR::Point(0.f, 7.f, 0.f));

//    std::list<SIRR::Line> lines({l1, l2, l3, l4});
//    SIRR::OrientationChecker checker;
//    std::cout << checker.check({l2.get_a(), l1.get_a(), l1.get_b()}) << std::endl;

    SIRR::Plyfile file;
    auto polygons(file.load_from("data/simple.ply"));
    std::list<SIRR::Line> merge_list;
    for (auto polygon : polygons)
        for (auto line : polygon.as_lines())
             merge_list.push_back(line);

    SIRR::LineIntersectionFinder finder;
    auto points(finder.find_intersections(merge_list));

    SIRR::SVGBuilder builder;
    builder.build("simple.svg", merge_list, points, true);

    return 0;
}
