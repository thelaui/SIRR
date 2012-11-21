#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

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
