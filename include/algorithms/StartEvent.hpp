#ifndef START_EVENT_HPP
#define START_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class Line3D;

class StartEvent : public Event {
    public:
        StartEvent(Point3D const& position, Line3D* l):
            Event(position, Event::START),
            l_(l) {}

        Line3D* get_l() const {
            return l_;
        }

    private:
        Line3D* l_;

};

}

#endif //START_EVENT_HPP



