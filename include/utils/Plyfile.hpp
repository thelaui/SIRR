#ifndef PLYFILE_HPP
#define PLYFILE_HPP

#include "primitives/Polygon.hpp"

#include <string>

namespace SIRR {

class Plyfile {
    public:
        Plyfile();

        std::list<Polygon> const load_from(std::string const& path_to_file) const;
        Polygon const load_as_one_polygon(std::string const& path_to_file) const;
        void save_to(Polygon const& polygon, std::string const& path_to_file) const;

};

}

#endif //PLYFILE_HPP

