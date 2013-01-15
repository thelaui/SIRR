#include "SIRR.hpp"

#include <iostream>

#define DIM 2
#define POINT_COUNT 100000
#define DEBUG_ENABLED 1

int main(int argc, const char** argv) {

    std::list<SIRR::Point<DIM>> points;

    for (unsigned i(0); i < POINT_COUNT; ++i)
        points.push_back(SIRR::Point<DIM>::get_random());

    SIRR::KRangeTree<DIM> range_tree;

#if DEBUG_ENABLED == 1
    SIRR::Timer timer;
    MESSAGE("Generating range-tree with %u points...", unsigned(points.size()));
    timer.reset();
    range_tree.generate<DIM>(points);
    timer.print_elapsed_time();
    MESSAGE("Done.\n");

    SIRR::KDTree<DIM> kd_tree;
    MESSAGE("Generating kd-tree with %u points...", unsigned(points.size()));
    timer.reset();
    kd_tree.generate(points);
    timer.print_elapsed_time();
    MESSAGE("Done.\n");

    unsigned query_repeat(100);

    for (unsigned i(0); i < 10; ++i) {
        SIRR::Point<DIM> min(std::vector<float>(DIM, 30.f - i * 20));
        SIRR::Point<DIM> max(std::vector<float>(DIM, 60.f + i * 20));
        std::list<SIRR::Point<DIM>> query_points({min, max});

        SIRR::BoundingBox<DIM> query_range(query_points);
        MESSAGE("Using bounding box [%f,%f;%f,%f].",
                query_range.get_min().get(0), query_range.get_min().get(1),
                query_range.get_max().get(0), query_range.get_max().get(1) );

        float average_time(0.f);

        MESSAGE("Querying range-tree...");
        for (unsigned i(0); i < query_repeat; ++i) {
            timer.reset();
            range_tree.range_search<DIM>(query_range);
            average_time += timer.get_elapsed_time()/query_repeat;
        }
        MESSAGE("Done.");
        MESSAGE("Needed %f seconds in average.\n", average_time);

        average_time = 0.f;

        MESSAGE("Querying kd-tree...");
        for (unsigned i(0); i < query_repeat; ++i) {
            timer.reset();
            kd_tree.search(&query_range);
            average_time += timer.get_elapsed_time()/query_repeat;
        }
        MESSAGE("Done.");
        MESSAGE("Needed %f seconds in average.\n", average_time);
    }

#else
    range_tree.generate<DIM>(points);
    std::list<SIRR::Point<3>> draw_points;
    for (auto point : points)
        draw_points.push_back(SIRR::Point<3>({point.get(0), point.get(1), 0.f}));

    SIRR::RenderWindow window(800, 600, "K-Range-Tree");

    float extends(0.f);
    std::list<SIRR::Point<DIM>> query_points({SIRR::Point<DIM>({-extends/2, -extends/2}),
                                            SIRR::Point<DIM>({extends/2, extends/2})});
    SIRR::BoundingBox<DIM> query_range(query_points);


    while (window.is_open()) {
        auto mouse_position(window.get_mouse_position_world().cropped_to<DIM>());

        query_points = {mouse_position - extends/2, mouse_position + extends/2};
        query_range = SIRR::BoundingBox<DIM>(query_points);
        auto searched_points(range_tree.range_search<DIM>(query_range));

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
