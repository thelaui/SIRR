#ifndef SVG_BUILDER_HPP
#define SVG_BUILDER_HPP

#include <list>

#include "primitives/Line.hpp"

namespace SIRR {

class SVGBuilder {
    public:
        SVGBuilder();

        void build(std::string const& path_to_file, std::list<Line> const& lines, std::list<Point> const& points) const;

};

}

#endif //SVG_BUILDER_HPP



