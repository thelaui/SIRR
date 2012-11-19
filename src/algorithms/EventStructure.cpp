#include "algorithms/EventStructure.hpp"

namespace SIRR {

EventStructure::EventStructure():
    events_() {}

void EventStructure::add_event(Event* event) {
    events_.insert(event);
}

Event* EventStructure::get_top() const {
    return *events_.begin();
}

void EventStructure::delete_top() {
    events_.erase(events_.begin());
}

bool EventStructure::empty() const {
    return events_.empty();
}

void EventStructure::print(std::ostream& os) const {
    for (auto event : events_)
        os << *event << std::endl;
}

}

std::ostream& operator<< (std::ostream& os, SIRR::EventStructure const& event_structure) {
    event_structure.print(os);
    return os;
}
