#include "SIRR.hpp"

#include <iostream>
#include <set>

int main(int argc, const char** argv) {

    SIRR::Line l1(SIRR::Point(0.5f, 0.5f, 0.f), SIRR::Point(0.f, 0.f, 0.f));
    SIRR::Line l2(SIRR::Point(2.f, 0.f, 0.f), SIRR::Point(0.f, 2.f, 0.f));

    std::cout << l1.intersects(l2) << std::endl;

    return 0;
}
