#include "algorithms/Event.hpp"

namespace SIRR {

Event::Event(Point const& position):
    position_(position) {}

Point const& Event::get_position() const {
    return position_;
}

}
