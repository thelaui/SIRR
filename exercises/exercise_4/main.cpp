#include "SIRR.hpp"

#include <iostream>

#define DIM 2

int main(int argc, const char** argv) {

    SIRR::Point<DIM> p1({1,6});
    SIRR::Point<DIM> p2({3,8});
    SIRR::Point<DIM> p3({1,7});
    SIRR::Point<DIM> p4({2,10});
    SIRR::Point<DIM> p5({4,9});

    std::list<SIRR::Point<DIM>> pl({p1, p2, p3, p4, p5});

    SIRR::KRangeTree<DIM> tree;
    tree.generate<DIM>(pl);
    //tree.print<DIM>(std::cout);

    SIRR::BoundingBox<DIM> bbox;
    bbox.include(p1);
    bbox.include(p4);

    std::cout << SIRR::Point<2>::get_random() << std::endl;

//    std::cout << "Bounding box:" << std::endl;
//    std::cout << bbox << std::endl;
//
//    std::cout << "Correct points:" << std::endl;
//    for (auto p : pl)
//        if (bbox.contains(p))
//            std::cout << p << std::endl;
//
//    std::cout << "Found points:" << std::endl;
//    auto points = tree.range_search<DIM>(bbox);
//    for (auto point : points)
//        std::cout << point << std::endl;

    return 0;
}
