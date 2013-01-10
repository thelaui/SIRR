#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Point<1> p1({1});
    SIRR::Point<1> p2({3});
    SIRR::Point<1> p3({5});
    SIRR::Point<1> p4({4});
    SIRR::Point<1> p5({2});

    std::list<SIRR::Point<1>> pl({p1, p2, p3, p4, p5});

    SIRR::KRangeTree<1> tree;
    tree.generate<1>(pl);
    std::cout << tree << std::endl;

    return 0;
}
