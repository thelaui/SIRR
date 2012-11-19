#ifndef EVENT_HPP
#define EVENT_HPP

#include "primitives/Point.hpp"

namespace SIRR {

class Event {
    public:
        enum EventType{START, END, INTERSECTION};

        Event(Point const& position, EventType type);
        virtual ~Event();

        Point const& get_position() const;

        EventType get_type() const;

        struct EventCompare {

            bool operator() (Event* lhs, Event* rhs) const {
                return COMPARE_Y(lhs->get_position(), rhs->get_position());
            }

        };

        void print(std::ostream& os) const;

    protected:
        Point position_;
        EventType type_;
};

}

std::ostream& operator<< (std::ostream& os, SIRR::Event const& event);

#endif //EVENT_HPP


