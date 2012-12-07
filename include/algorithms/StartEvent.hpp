#ifndef START_EVENT_HPP
#define START_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class Line;

class StartEvent : public Event {
    public:
        StartEvent(Point3D const& position, Line* l):
            Event(position, Event::START),
            l_(l) {}

        Line* get_l() const {
            return l_;
        }

    private:
        Line* l_;

};

}

#endif //START_EVENT_HPP



