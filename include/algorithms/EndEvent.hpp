#ifndef END_EVENT_HPP
#define END_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class EndEvent : public Event {
    public:
        EndEvent(Point const& position):
            Event(position) {}

};

}

#endif //END_EVENT_HPP
