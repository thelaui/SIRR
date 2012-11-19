#ifndef END_EVENT_HPP
#define END_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class Line;

class EndEvent : public Event {
    public:
        EndEvent(Point const& position, Line* l):
            Event(position, Event::END),
            l_(l) {}

    Line* get_l() const {
            return l_;
        }

    private:
        Line* l_;

};

}

#endif //END_EVENT_HPP
