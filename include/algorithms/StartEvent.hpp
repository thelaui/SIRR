#ifndef START_EVENT_HPP
#define START_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class StartEvent : public Event {
    public:
        StartEvent(Point const& position):
            Event(position) {}

};

}

#endif //START_EVENT_HPP



