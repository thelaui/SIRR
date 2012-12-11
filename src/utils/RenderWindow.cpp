#include "utils/RenderWindow.hpp"
#include "primitives/BoundingBox.hpp"

#include <iostream>

namespace SIRR {

RenderWindow::RenderWindow(unsigned width, unsigned height, std::string const& title):
    window_(sf::VideoMode(width, height), title),
    max_(),
    min_(std::vector<float>(3, FLT_MAX)),
    mouse_position_() {}

bool RenderWindow::is_open() const{

    return window_.IsOpened();
}

void RenderWindow::clear() {
    window_.Clear(sf::Color::White);
}

void RenderWindow::flush() {
    sf::Event event;
        while (window_.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
                window_.Close();
            if (event.Type == sf::Event::MouseMoved) {
                mouse_position_.set(0, event.MouseMove.X);
                mouse_position_.set(1, event.MouseMove.Y);
            }
        }

    window_.Display();
}

void RenderWindow::draw(std::list<Point<3>> const& points,
                        unsigned pr, unsigned pg, unsigned pb,
                        std::list<Line<3>> const& lines,
                        unsigned lr, unsigned lg, unsigned lb) {

    BoundingBox<3> dimensions(points);
//    for (auto line : lines) {
//        dimensions.include(line.get_a());
//        dimensions.include(line.get_b());
//    }

    if (dimensions.get_min() < min_)
        min_ = dimensions.get_min();
    if (dimensions.get_max() > max_)
        max_ = dimensions.get_max();

    for (auto line : lines) {
        Point<3> a(world_to_screen_coord(line.get_a()));
        Point<3> b(world_to_screen_coord(line.get_b()));

        window_.Draw(sf::Shape::Line(a.get(0), a.get(1),
                                     b.get(0), b.get(1),
                                     2.f, sf::Color(lr, lg, lb)));
    }

    for (auto point : points) {
        Point<3> p(world_to_screen_coord(point));
        window_.Draw(sf::Shape::Circle(p.get(0), p.get(1), 3.f,
                                       sf::Color(pr, pg, pb),
                                       2.f, sf::Color(100, 100, 100)));
    }

}

Point<3> const& RenderWindow::get_mouse_position() const {
    return mouse_position_;
}

Point<3> const RenderWindow::get_mouse_position_world() const {
    Point<3> window_dims({float(window_.GetWidth()-20),
                          float(window_.GetHeight()-20), 1.f});

    Point<3> result(Point<3>({mouse_position_.get(0), window_.GetHeight() - mouse_position_.get(1), 1.f})
                    / window_dims * (max_ - min_) + min_);

    return result;
}


Point<3> const RenderWindow::world_to_screen_coord(Point<3> const& point) {
    Point<3> window_dims({float(window_.GetWidth()-20),
                          float(window_.GetHeight()-20), 1.f});
    Point<3> result(((point - min_) / (max_ - min_)) * window_dims);
    return Point<3>({result.get(0) + 10, window_.GetHeight()-result.get(1) -10, 0.f});
}

}
