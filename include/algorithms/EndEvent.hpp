#ifndef END_EVENT_HPP
#define END_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class Line3D;

class EndEvent : public Event {
    public:
        EndEvent(Point3D const& position, Line3D* l):
            Event(position, Event::END),
            l_(l) {}

    Line3D* get_l() const {
            return l_;
        }

    private:
        Line3D* l_;

};

}

#endif //END_EVENT_HPP
