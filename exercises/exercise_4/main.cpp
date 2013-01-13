#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Point<2> p1({1, -1});
    SIRR::Point<2> p2({3, 2});
    SIRR::Point<2> p3({5, 10});
//    SIRR::Point<3> p4({4, 1, 1});
//    SIRR::Point<3> p5({2, 3, 3});

    std::list<SIRR::Point<2>> pl({p1, p2, p3});//, p4, p5});

    SIRR::KRangeTree<2> tree;
    tree.generate<2>(pl);
    std::cout << tree << std::endl;

//    SIRR::BoundingBox<3> bbox(pl);
//    auto points = tree.range_search<3>(bbox);
//    for (auto point : points)
//        std::cout << point << std::endl;

    return 0;
}
