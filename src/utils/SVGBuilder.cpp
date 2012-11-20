#include <fstream>
#include <sstream>

#include "utils/SVGBuilder.hpp"

namespace SIRR {

SVGBuilder::SVGBuilder():
    max_x_(0.f),
    max_y_(0.f){}

void SVGBuilder::build(std::string const& path_to_file, std::list<Line> const& lines, std::list<Point> const& points) {

    for (auto line : lines) {
        float x1(line.get_a().get_x() * 100.f);
        float y1(line.get_a().get_y() * 100.f);
        float x2(line.get_b().get_x() * 100.f);
        float y2(line.get_b().get_y() * 100.f);

        max_x_ = std::max(max_x_, std::max(x1, x2));
        max_y_ = std::max(max_y_, std::max(y1, y2));
    }

    std::ofstream file(path_to_file);
    file << "<!DOCTYPE html>\n<html>\n<body bgcolor=\"white\">\n\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
         << "width=\""<< int(max_x_ + 50.f) <<"px\" "
         << "height=\""<< int(max_y_ + 20.f) <<"px\">\n";

    for (auto line : lines) {
        file << get_line_string(line);
        file << get_circle_string(line.get_a(), 5, 100, 100, 100, 100, 100, 100);
        file << get_circle_string(line.get_b(), 5, 100, 100, 100, 100, 100, 100);
    }

    for (auto point : points) {
        file << get_circle_string(point, 9, 200, 240, 120, 100, 100, 100);
    }

    file << "</svg>\n</body>\n</html>";

    file.close();
}

std::string const SVGBuilder::get_line_string(Line const& line) const {
    float x1(line.get_a().get_x() * 100.f);
    float y1(line.get_a().get_y() * 100.f);
    float x2(line.get_b().get_x() * 100.f);
    float y2(line.get_b().get_y() * 100.f);

    std::stringstream line_stream;
    line_stream << "<line x1=\"" << x1
                <<"\" y1=\"" << max_y_ + 20.f - y1
                <<"\" x2=\"" << x2
                <<"\" y2=\"" << max_y_ + 20.f - y2
                <<"\" style=\"stroke:rgb(100,100,100);stroke-width:2\" />\n";


    return line_stream.str();
}

std::string const SVGBuilder::get_text_string(std::string const& text, int pos_x, int pos_y) const {
    std::stringstream text_stream;
    text_stream << "<text x=\"" << pos_x
                << "\" y=\"" << pos_y
                << "\" fill=\"rgb(100,100,100)\">"
                << text << "</text>\n";

    return text_stream.str();
}

std::string const SVGBuilder::get_circle_string(Point const& point, int radius,
                                             int r, int g, int b, int sr, int sg, int sb) const {
    std::stringstream circle_stream;
    circle_stream << "<circle cx=\"" << point.get_x() * 100.f
                  << "\" cy=\"" << max_y_ + 20.f - point.get_y() * 100.f
                  << "\" r=\""<< radius
                  << "\" stroke=\"rgb("<< sr << "," << sg << "," << sb <<")"
                  << "\" fill=\"rgb("<< r << "," << g << "," << b <<")\" />\n";

    std::stringstream label_stream;
    label_stream  << "(" << point.get_x() << ", " << point.get_y() << ")";
    circle_stream << get_text_string(label_stream.str(), point.get_x() * 100.f + 10.f, max_y_ + 20.f - point.get_y() * 100.f + 15.f);

    return circle_stream.str();
}

}


