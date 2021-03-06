#ifndef RENDER_WINDOW_HPP
#define RENDER_WINDOW_HPP

#include "SFML/Graphics.hpp"

#include <string>
#include <list>

#include "primitives/Line.hpp"

namespace SIRR {

class RenderWindow {
    public:
        RenderWindow(unsigned width, unsigned height, std::string const& title);

        bool is_open() const;

        void clear();
        void flush();

        void draw(std::list<Point<3>> const& points,
                  unsigned pr = 200, unsigned pg = 240, unsigned pb = 120,
                  std::list<Line<3>> const& lines = std::list<Line<3>>(),
                  unsigned lr = 100, unsigned lg = 100, unsigned lb = 100);

        Point<3> const& get_mouse_position() const;
        Point<3> const get_mouse_position_world() const;
        int get_button_state() const;
        int get_mouse_wheel_delta() const;

        Point<3> const& get_world_min() const;
        Point<3> const& get_world_max() const;


    private:

        Point<3> const world_to_screen_coord(Point<3> const& point);

        sf::RenderWindow window_;
        Point<3> max_, min_;
        Point<3> mouse_position_;
        int button_state_;
        int mouse_wheel_delta_;
};

}

#endif //RENDER_WINDOW_HPP


