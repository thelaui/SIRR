#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Plyfile file;
    auto polygons(file.load_from("data/sphere.ply"));

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

    float extends(40.f);

    std::list<SIRR::Point<3>> query_points({SIRR::Point<3>({-extends/2, -extends/2, 0}),
                                            SIRR::Point<3>({extends/2, extends/2, 0})});
    SIRR::BoundingBox<3> query_box(query_points);

    SIRR::HyperCircle<3> query_circle(SIRR::Point<3>({0, 0, 0}), extends);

    SIRR::RenderWindow window(800, 600, "kd-Tree");

    while (window.is_open()) {
        auto mouse_position(window.get_mouse_position_world());
        auto button_state(window.get_button_state());
        SIRR::TestingShape<3>* query_range(NULL);

//        std::cout << mouse_position << std::endl;
        extends += 5.f * window.get_mouse_wheel_delta();

        if (button_state == 0) {
            query_points = {mouse_position - extends/2, mouse_position + extends/2};
            query_box = SIRR::BoundingBox<3>(query_points);
            query_range = &query_box;
        } else if (button_state == 1) {
            query_circle = SIRR::HyperCircle<3>(mouse_position, extends);
            query_range = &query_circle;
        }

        auto searched_points(tree.search(query_range));
        window.clear();

        window.draw(points, 200, 240, 120, {}, 200, 200, 200);
        window.draw({}, 0, 0, 0, query_range->as_2D_lines(), 200, 40, 40);
        window.draw(searched_points, 200, 40, 40);

        window.flush();
    }

    return 0;
}
