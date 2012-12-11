#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Plyfile file;
    auto polygons(file.load_from("data/sphere.ply"));

//    SIRR::Point<3> p1({0,0,0});
//    SIRR::Point<3> p2({4,4,0});
//    SIRR::Point<3> p3({5,5,0});
//    SIRR::Point<3> p4({3,2,0});
//    std::list<SIRR::Point<3>> points({p1,p2,p3,p4});
//
//    SIRR::HyperCircle<3> circle(p1, 5);
//    if (circle.contains(p3))
//        std::cout << "point inside" << std::endl;
//
//    SIRR::BoundingBox<3> box(points);
//    std::cout << box << std::endl;


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
        auto box_lines(box->as_2D_lines());
        lines.insert(lines.end(), box_lines.begin(), box_lines.end());
    }

    std::list<SIRR::Point<3>> query_points({SIRR::Point<3>({-50, -50, 0}),
                                            SIRR::Point<3>({50, 50, 0})});
    SIRR::BoundingBox<3> query_box(query_points);

    SIRR::HyperCircle<3> query_circle(SIRR::Point<3>({0, 0, 0}), 60);

    SIRR::RenderWindow window(800, 600, "kd-Tree");

    while (window.is_open()) {
        auto mouse_position(window.get_mouse_position_world());
        query_points = {mouse_position - 50, mouse_position + 50};
        query_box = SIRR::BoundingBox<3>(query_points);
        auto searched_points(tree.search(&query_box));
        window.clear();

       // std::cout << window.get_mouse_position_world() << std::endl;
        window.draw(points, 200, 240, 120, lines, 200, 200, 200);
        window.draw({}, 0, 0, 0, query_box.as_2D_lines(), 200, 40, 40);
//        window.draw({}, 0, 0, 0, query_circle.as_2D_lines(), 200, 40, 40);
        window.draw(searched_points, 200, 40, 40);

        window.flush();
    }

    return 0;
}
