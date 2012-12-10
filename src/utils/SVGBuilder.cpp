#include <fstream>
#include <sstream>
#include <iostream>

#include "utils/SVGBuilder.hpp"

namespace SIRR {

SVGBuilder::SVGBuilder():
    max_x_(0.f),
    min_x_(0.f),
    max_y_(0.f),
    min_y_(0.f),
    labels_enabled_(true){}

void SVGBuilder::build(std::string const& path_to_file, std::list<Line3D> const& lines, std::list<Point3D> const& points, bool enable_labels) {
    labels_enabled_ = enable_labels;

    for (auto line : lines) {
        float x1(line.get_a().get_x());
        float y1(line.get_a().get_y());
        float x2(line.get_b().get_x());
        float y2(line.get_b().get_y());

        max_x_ = std::max(max_x_, std::max(x1, x2));
        min_x_ = std::min(min_x_, std::min(x1, x2));
        max_y_ = std::max(max_y_, std::max(y1, y2));
        min_y_ = std::min(min_y_, std::min(y1, y2));

    }
    std::ofstream file(path_to_file);
    auto extends(to_pixel(Point3D(max_x_, 0.f)));

    file << "<!DOCTYPE html>\n<html>\n<body bgcolor=\"white\">\n\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
         << "width=\""<< int(extends.get_x() + 50.f) <<"px\" "
         << "height=\""<< int(extends.get_y() + 20.f) <<"px\">\n";

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

Point3D const SVGBuilder::to_pixel(Point3D const& p) const {
    return Point3D((p.get_x()  + std::abs(int(min_x_))) / (max_x_ - min_x_) * 1000.f + 20.f,
                  (max_y_ - (p.get_y() + std::abs(int(min_y_)))) / (max_y_ - min_y_) * 1000.f + 20.f);
}

std::string const SVGBuilder::get_line_string(Line3D const& line) const {
    auto a(to_pixel(line.get_a()));
    auto b(to_pixel(line.get_b()));

    std::stringstream line_stream;
    line_stream << "<line x1=\"" << a.get_x()
                <<"\" y1=\"" << a.get_y()
                <<"\" x2=\"" << b.get_x()
                <<"\" y2=\"" << b.get_y()
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

std::string const SVGBuilder::get_circle_string(Point3D const& point, int radius,
                                             int r, int g, int b, int sr, int sg, int sb) const {
    auto p(to_pixel(point));
    std::stringstream circle_stream;
    circle_stream << "<circle cx=\"" << p.get_x()
                  << "\" cy=\"" << p.get_y()
                  << "\" r=\""<< radius
                  << "\" stroke=\"rgb("<< sr << "," << sg << "," << sb <<")"
                  << "\" fill=\"rgb("<< r << "," << g << "," << b <<")\" />\n";

    if (labels_enabled_) {
        std::stringstream label_stream;
        label_stream  << "(" << point.get_x() << ", " << point.get_y() << ")";
        circle_stream << get_text_string(label_stream.str(), p.get_x() + 10.f,p.get_y() + 15.f);
    }

    return circle_stream.str();
}

}


