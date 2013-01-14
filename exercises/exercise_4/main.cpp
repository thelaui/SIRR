#include "SIRR.hpp"

#include <iostream>

#define DIM 2
#define POINT_COUNT 10
#define DEBUG 0

int main(int argc, const char** argv) {

    SIRR::Point<DIM> p1({1,6});
    SIRR::Point<DIM> p2({3,8});
    SIRR::Point<DIM> p3({5,7});
    SIRR::Point<DIM> p4({2,10});
    SIRR::Point<DIM> p5({4,9});

//    std::list<SIRR::Point<DIM>> points({p1, p2, p3, p4, p5});

    std::list<SIRR::Point<DIM>> points;

    for (unsigned i(0); i < POINT_COUNT; ++i)
        points.push_back(SIRR::Point<DIM>::get_random());


    SIRR::KRangeTree<DIM> tree;
    tree.generate<DIM>(points);

    tree.print<DIM>(std::cout);

#if DEBUG == 1

    std::list<SIRR::Point<DIM>> query_points({SIRR::Point<DIM>({4.5, 8}),
                                              SIRR::Point<DIM>({5, 8.5})});
    SIRR::BoundingBox<DIM> query_range(query_points);

    auto searched_points(tree.range_search<DIM>(query_range));


    std::cout << "Bounding box:" << std::endl;
    std::cout << query_range << std::endl;

    std::cout << "Correct points:" << std::endl;
    for (auto point : points)
        if (query_range.contains(point))
            std::cout << point << std::endl;

    std::cout << "Found points:" << std::endl;
    for (auto point : searched_points)
        std::cout << point << std::endl;

#else
    std::list<SIRR::Point<3>> draw_points;
    for (auto point : points)
        draw_points.push_back(SIRR::Point<3>({point.get(0), point.get(1), 0.f}));

    SIRR::RenderWindow window(800, 600, "K-Range-Tree");

    float extends(5.f);
    std::list<SIRR::Point<DIM>> query_points({SIRR::Point<DIM>({-extends/2, -extends/2}),
                                            SIRR::Point<DIM>({extends/2, extends/2})});
    SIRR::BoundingBox<DIM> query_range(query_points);


    while (window.is_open()) {
        auto mouse_position(window.get_mouse_position_world().cropped_to<DIM>());

        query_points = {mouse_position - extends/2, mouse_position + extends/2};
        query_range = SIRR::BoundingBox<DIM>(query_points);
        std::cout << query_range << std::endl;
        auto searched_points(tree.range_search<DIM>(query_range));

        std::list<SIRR::Point<3>> draw_searched_points;
        for (auto point : searched_points)
            draw_searched_points.push_back(SIRR::Point<3>({point.get(0), point.get(1), 0.f}));

        window.clear();

        window.draw(draw_points, 200, 240, 120, {}, 200, 200, 200);
        window.draw({}, 0, 0, 0, query_range.as_2D_lines(), 200, 40, 40);
        window.draw(draw_searched_points, 200, 40, 40);

        window.flush();

        extends += SIRR::distance(window.get_world_max(), window.get_world_min()) / 50.f
                   * window.get_mouse_wheel_delta();
        extends = std::max(SIRR::distance(window.get_world_max(), window.get_world_min()) / 10, extends);
    }
#endif

    return 0;
}
