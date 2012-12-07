#ifndef SVG_BUILDER_HPP
#define SVG_BUILDER_HPP

#include <list>

#include "primitives/Line.hpp"
#include "primitives/Point3D.hpp"

namespace SIRR {

class SVGBuilder {
    public:
        SVGBuilder();

        void build(std::string const& path_to_file, std::list<Line> const& lines, std::list<Point3D> const& points, bool enable_labels);

    private:
        float max_x_, min_x_, max_y_, min_y_;
        bool labels_enabled_;

        Point3D const to_pixel(Point3D const& p) const;
        std::string const get_line_string(Line const& line) const;
        std::string const get_text_string(std::string const& text, int pos_x, int pos_y) const;
        std::string const get_circle_string(Point3D const& point, int radius,
                                             int r, int g, int b, int sr, int sg, int sb) const;
};

}

#endif //SVG_BUILDER_HPP



