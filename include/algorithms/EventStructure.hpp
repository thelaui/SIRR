#ifndef EVENT_STRUCTURE_HPP
#define EVENT_STRUCTURE_HPP

#include <set>

#include "algorithms/Event.hpp"

namespace SIRR {

class EventStructure {
    public:
        EventStructure();

        void add_event(Event* event);

        Event* get_top() const;
        void delete_top();

        bool empty() const;

        void print(std::ostream& os) const;

    private:
        std::multiset<Event*, Event::EventCompare> events_;
};

}

std::ostream& operator<< (std::ostream& os, SIRR::EventStructure const& event_structure);

#endif //EVENT_STRUCTURE_HPP



