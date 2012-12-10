#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Plyfile file;
    auto polygons(file.load_from("data/simple.ply"));
//
//    SIRR::Point<3> p1({5,3,0});
//    SIRR::Point<3> p2({4,4,0});
//    SIRR::Point<3> p3({2,3,0});
//    SIRR::Point<3> p4({3,2,0});
//    std::list<SIRR::Point<3>> points({p1,p2,p3,p4});

    std::list<SIRR::Point<3>> points;

    for (auto polygon : polygons) {
        auto poly_lines(polygon.as_lines());
        for (auto line : poly_lines) {
            points.push_back(SIRR::Point<3>({line.get_a().get_x(), line.get_a().get_y(),0}));
            points.push_back(SIRR::Point<3>({line.get_b().get_x(), line.get_b().get_y(),0}));
        }
    }

    SIRR::KDTree<3> tree;
    tree.build(points);

    auto boxes(tree.get_bounding_boxes());

    std::list<SIRR::Line<3>> lines;
    for (auto box : boxes) {
        auto box_lines(box.as_2D_lines());
        lines.insert(lines.end(), box_lines.begin(), box_lines.end());
    }

    std::list<SIRR::Point<3>> query_points({SIRR::Point<3>({2, 4, 0}),
                                            SIRR::Point<3>({4, 5, 0})});
    SIRR::BoundingBox<3> query_box(query_points);

    auto searched_points(tree.search(query_box));
    for (auto point : searched_points)
        std::cout << point << std::endl;

    SIRR::RenderWindow window(800, 600, "kd-Tree");

    while (window.is_open()) {
        window.clear();

        window.draw(points, 200, 240, 120, lines, 200, 200, 200);
        window.draw({}, 0, 0, 0, query_box.as_2D_lines(), 200, 40, 40);
        window.draw(searched_points, 200, 40, 40);

        window.flush();
    }

    return 0;
}
