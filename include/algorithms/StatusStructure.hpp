#ifndef STATUS_STRUCTURE_HPP
#define STATUS_STRUCTURE_HPP

#include <vector>

#include "primitives/Point.hpp"
#include "algorithms/OrientationChecker.hpp"

namespace SIRR {

class Line;

class StatusStructure {
    public:
        StatusStructure();

        void add_line(Line* line);
        void remove_line(Line* line);

        void swap(Line* l1, Line* l2);

        void print(std::ostream& os) const;


    private:
        std::vector<Line*> lines_;

        std::vector<Line*>::iterator find_higher(Point const& query_point);
        std::vector<Line*>::iterator find_closest(Line* line);

};

}

std::ostream& operator<< (std::ostream& os, SIRR::StatusStructure const& status_structure);

#endif //STATUS_STRUCTURE_HPP




