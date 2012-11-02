#include "SIRR.hpp"

#include <iostream>

int main(int argc, const char** argv) {

    SIRR::Plyfile plyfile;
    SIRR::ConvexHullBuilder ch_builder;
    plyfile.save_to(ch_builder.build_hull(plyfile.load_from("data/sphere.ply")),"sphere_hull.ply");

    return 0;
}
