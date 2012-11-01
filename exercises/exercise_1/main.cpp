#include "utils/Plyfile.hpp"

#include <iostream>

int main() {
    SIRR::Plyfile plyfile;

    SIRR::Polygon poly = plyfile.load_from("data/simple.ply");
    plyfile.save_to(poly, "test.ply");

    return 0;
}
