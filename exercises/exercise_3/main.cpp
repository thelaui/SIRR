#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Plyfile file;
    auto polygons(file.load_from("data/simple.ply"));

    std::list<SIRR::Line> lines;
    for (auto polygon : polygons) {
        auto poly_lines(polygon.as_lines());
        lines.insert(lines.end(), poly_lines.begin(), poly_lines.end());
    }

    SIRR::SVGBuilder builder;
    builder.build("test.svg", lines, {}, true);

    SIRR::RenderWindow window(800, 600, "kd-Tree");

    while (window.is_open()) {
        window.clear();

        window.draw({}, 0, 0, 0, lines);

        window.flush();
    }

//    SIRR::Point<3> p1({1,1,1});
//    SIRR::Point<3> p2({2,2,2});
//    SIRR::Point<3> p3({3,2,2});
//
//    SIRR::BoundingBox<3> box({p1, p2});
//    std::cout << box << std::endl;
//    box.include(p3);
//    std::cout << box << std::endl;


    return 0;
}
