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

    SIRR::Point<3> p1({0,0,0});
    SIRR::Point<3> p2({5,5,0});
    SIRR::Point<3> p3({2,2,0});
    SIRR::Point<3> p4({3,2,0});

    SIRR::BoundingBox<3> large_box({p1, p2});
    SIRR::BoundingBox<3> small_box({p3, p4});

    if (small_box.is_inside(large_box))
        std::cout << "small in large" << std::endl;
    if (large_box.is_inside(small_box))
        std::cout << "large in small" << std::endl;
    if (large_box.intersects(small_box))
        std::cout << "large intersects small" << std::endl;
    if (small_box.intersects(large_box))
        std::cout << "small intersects large" << std::endl;


    return 0;
}
