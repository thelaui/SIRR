#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Plyfile file;
    SIRR::ConvexHullBuilder builder;
    file.save_to(builder.build_hull(file.load_as_one_polygon("data/sphere.ply")), "sphere_hull_2.ply");

    return 0;
}
