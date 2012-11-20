#ifndef SVG_BUILDER_HPP
#define SVG_BUILDER_HPP

#include <list>

#include "primitives/Line.hpp"
#include "primitives/Point.hpp"

namespace SIRR {

class SVGBuilder {
    public:
        SVGBuilder();

        void build(std::string const& path_to_file, std::list<Line> const& lines, std::list<Point> const& points);

    private:
        float max_x_, max_y_;

        std::string const get_line_string(Line const& line) const;
        std::string const get_text_string(std::string const& text, int pos_x, int pos_y) const;
        std::string const get_circle_string(Point const& point, int radius,
                                             int r, int g, int b, int sr, int sg, int sb) const;
};

}

#endif //SVG_BUILDER_HPP



