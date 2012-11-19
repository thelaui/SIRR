#ifndef INTERSECTION_EVENT_HPP
#define INTERSECTION_EVENT_HPP

#include "algorithms/Event.hpp"

namespace SIRR {

class Line;

class IntersectionEvent : public Event {
    public:
        IntersectionEvent(Point const& position, Line* l1, Line* l2):
            Event(position, Event::INTERSECTION),
            l1_(l1),
            l2_(l2) {}

        Line* get_l1() const {
            return l1_;
        }

        Line* get_l2() const {
            return l2_;
        }

    private:
        Line *l1_, *l2_;

};

}

#endif //INTERSECTION_EVENT_HPP
