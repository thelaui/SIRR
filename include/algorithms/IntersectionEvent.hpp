#ifndef INTERSECTION_EVENT_HPP
#define INTERSECTION_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class IntersectionEvent : public Event {
    public:
        IntersectionEvent(Point const& position):
            Event(position) {}

};

}

#endif //INTERSECTION_EVENT_HPP
