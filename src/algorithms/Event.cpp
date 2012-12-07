#include "algorithms/Event.hpp"

namespace SIRR {

Event::Event(Point3D const& position, EventType type):
    position_(position),
    type_(type) {}

Event::~Event() {}

Point3D const& Event::get_position() const {
    return position_;
}

Event::EventType Event::get_type() const {
    return type_;
}

void Event::print(std::ostream& os) const {
    std::string type_string("Invalid event");

    switch (type_) {
        case START:
            type_string = "Start event";
            break;
        case END:
            type_string = "End event";
            break;
        case INTERSECTION:
            type_string = "Intersection event";
            break;
        default: break;
    }

    os << type_string << " at " << position_ ;
}

}

std::ostream& operator<< (std::ostream& os, SIRR::Event const& event) {
    event.print(os);
    return os;
}
