#include <fstream>
#include <sstream>

#include "utils/SVGBuilder.hpp"

namespace SIRR {

SVGBuilder::SVGBuilder() {}

void SVGBuilder::build(std::string const& path_to_file, std::list<Line> const& lines, std::list<Point> const& points) const {
    std::stringstream line_stream;

    float max_x(0.f), max_y(0.f);

    for (auto line : lines) {
        float x1(line.get_a().get_x() * 100.f);
        float y1(line.get_a().get_y() * 100.f);
        float x2(line.get_b().get_x() * 100.f);
        float y2(line.get_b().get_y() * 100.f);

        max_x = std::max(max_x, std::max(x1, x2));
        max_y = std::max(max_y, std::max(y1, y2));

        line_stream << "<line x1=\"" << x1
                    <<"\" y1=\"" << y1
                    <<"\" x2=\"" << x2
                    <<"\" y2=\"" << y2
                    <<"\" style=\"stroke:rgb(100,100,100);stroke-width:2\" />\n";
    }

    std::ofstream file(path_to_file);
    file << "<!DOCTYPE html>\n<html>\n<body bgcolor=\"white\">\n\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
         << "width=\""<< int(max_x + 20.f) <<"px\" "
         << "height=\""<< int(max_y + 20.f) <<"px\">\n";

    file << line_stream.str();

    for (auto point : points) {
        file << "<circle cx=\"" << point.get_x() * 100.f
             << "\" cy=\"" << point.get_y() * 100.f
             << "\" r=\"3\" stroke=\"none\" fill=\"rgb(200,240,120)\" />\n";
    }

    file << "</svg>\n</body>\n</html>";

    file.close();
}

}


