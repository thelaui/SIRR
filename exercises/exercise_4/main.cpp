#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Point<1> p1({1});
    SIRR::Point<1> p2({3});
    SIRR::Point<1> p3({5});
    SIRR::Point<1> p4({2});
    SIRR::Point<1> p5({4});

    std::list<SIRR::Point<1>> pl({p1, p2, p3, p4, p5});

    SIRR::KRangeTree<1> tree;
    tree.generate<1>(pl);
    //std::cout << tree << std::endl;

    SIRR::BoundingBox<1> bbox;
    bbox.include(p2);
    bbox.include(p5);
    auto points = tree.range_search<1>(bbox);
    for (auto point : points)
        std::cout << point << std::endl;

    return 0;
}
