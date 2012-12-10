#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

//    SIRR::Plyfile file;
//    auto polygons(file.load_from("data/simple.ply"));
//
//    std::list<SIRR::Line> lines;
//    for (auto polygon : polygons) {
//        auto poly_lines(polygon.as_lines());
//        lines.insert(lines.end(), poly_lines.begin(), poly_lines.end());
//    }
//
//    SIRR::SVGBuilder builder;
//    builder.build("test.svg", lines, {}, true);
//
//    SIRR::RenderWindow window(800, 600, "kd-Tree");
//
//    while (window.is_open()) {
//        window.clear();
//
//        window.draw({}, 0, 0, 0, lines);
//
//        window.flush();
//    }

    SIRR::Point<2> p1({5,3});
    SIRR::Point<2> p2({4,4});
    SIRR::Point<2> p3({2,2});
    SIRR::Point<2> p4({3,2});
    std::list<SIRR::Point<2>> l({p1,p2,p3,p4});
    SIRR::KDTree<2> tree;
    tree.build(l);
    std::cout << tree << std::endl;


    return 0;
}
