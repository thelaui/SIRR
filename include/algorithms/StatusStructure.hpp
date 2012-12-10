#ifndef STATUS_STRUCTURE_HPP
#define STATUS_STRUCTURE_HPP

#include <vector>

#include "primitives/Point3D.hpp"
#include "algorithms/OrientationChecker.hpp"
#include "algorithms/EventStructure.hpp"

namespace SIRR {

class Line3D;
class StartEvent;
class EndEvent;
class IntersectionEvent;

class StatusStructure {
    public:
        StatusStructure();

        Point3D const process_event(Event* event, EventStructure& event_structure);

        void print(std::ostream& os) const;


    private:
        std::vector<Line3D*> lines_;

        void add_line(StartEvent* event, EventStructure& event_structure);
        void remove_line(EndEvent* event, EventStructure& event_structure);
        void swap(IntersectionEvent* event, EventStructure& event_structure);


        std::vector<Line3D*>::iterator find_higher(Line3D* query_line);
        std::vector<Line3D*>::iterator find_closest(Line3D* line);

};

}

std::ostream& operator<< (std::ostream& os, SIRR::StatusStructure const& status_structure);

#endif //STATUS_STRUCTURE_HPP




