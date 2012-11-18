#include "algorithms/EventStructure.hpp"

namespace SIRR {

EventStructure::EventStructure():
    events_() {}

void EventStructure::add_event(Event const& event) {
    events_.insert(event);
}

Event const& EventStructure::get_max() const {
    return *events_.begin();
}

void EventStructure::delete_max() {
    events_.erase(events_.begin());
}

}
