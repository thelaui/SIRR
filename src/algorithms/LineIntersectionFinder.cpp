#include "algorithms/LineIntersectionFinder.hpp"

#include "algorithms/EventStructure.hpp"
#include "algorithms/StatusStructure.hpp"
#include "algorithms/StartEvent.hpp"
#include "algorithms/EndEvent.hpp"

#include <iostream>

namespace SIRR {

LineIntersectionFinder::LineIntersectionFinder() {}

std::list<Point> const LineIntersectionFinder::find_intersections(std::list<Line>& lines) const {
    EventStructure event_structure;
    StatusStructure status_structure;

    std::list<Point> intersections;

    for (auto line = lines.begin(); line != lines.end(); ++line) {
        event_structure.add_event(new StartEvent(line->get_a(), &(*line)));
        event_structure.add_event(new EndEvent(line->get_b(), &(*line)));
    }

    while (!event_structure.empty()) {
//        std::cout << "Event structure:\n" << event_structure << std::endl;
        Event* event(event_structure.get_top());
        event_structure.delete_top();
        Point intersection(status_structure.process_event(event, event_structure));
        if (intersection.get_z() != -1)
            intersections.push_back(intersection);

//        std::cout << "Status structure:\n" << status_structure << std::endl;
    }

    return intersections;
}

}
