#ifndef EVENT_STRUCTURE_HPP
#define EVENT_STRUCTURE_HPP

#include <set>

#include "algorithms/Event.hpp"

namespace SIRR {

class EventStructure {
    public:
        EventStructure();

        void add_event(Event const& event);

        Event const& get_max() const;
        void delete_max();


    private:
        std::multiset<Event, Event::EventCompare> events_;
};

}

#endif //EVENT_STRUCTURE_HPP



