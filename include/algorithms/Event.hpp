#ifndef EVENT_HPP
#define EVENT_HPP

#include "primitives/Point.hpp"

namespace SIRR {

class Event {
    public:
        Event(Point const& position);

        virtual Point const& get_position() const;

        struct EventCompare {

            bool operator() (Event const& lhs, Event const& rhs) const {
                return COMPARE_X(lhs.get_position(), rhs.get_position());
            }

        };


    protected:
        Point position_;
};

}

#endif //EVENT_HPP


