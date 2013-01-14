#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Point<2> p1({1,6});
    SIRR::Point<2> p2({3,8});
    SIRR::Point<2> p3({5,7});
    SIRR::Point<2> p4({2,10});
    SIRR::Point<2> p5({4,9});

    std::list<SIRR::Point<2>> pl({p1, p2, p3, p4, p5});

    SIRR::KRangeTree<2> tree;
    tree.generate<2>(pl);
//    std::cout << tree << std::endl;

    SIRR::BoundingBox<2> bbox;
    bbox.include(p3);
    bbox.include(p4);
    std::cout << bbox << std::endl;
    auto points = tree.range_search<2>(bbox);
    for (auto point : points)
        std::cout << point << std::endl;

    return 0;
}
