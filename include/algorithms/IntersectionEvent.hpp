#ifndef INTERSECTION_EVENT_HPP
#define INTERSECTION_EVENT_HPP

#include "algorithms/Event.hpp"

#include "primitives/Line3D.hpp"

namespace SIRR {

class IntersectionEvent : public Event {
    public:
        IntersectionEvent(Point3D const& position, Line3D* l1, Line3D* l2):
            Event(position, Event::INTERSECTION),
            l1_(l1),
            l2_(l2) {}

        Line3D* get_l1() const {
            return l1_;
        }

        Line3D* get_l2() const {
            return l2_;
        }

    private:
        Line3D *l1_, *l2_;

};

}

#endif //INTERSECTION_EVENT_HPP
