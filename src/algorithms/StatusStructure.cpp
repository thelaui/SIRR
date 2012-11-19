#include "algorithms/StatusStructure.hpp"

#include "primitives/Line.hpp"

#include <iostream>

namespace SIRR {

StatusStructure::StatusStructure():
    lines_() {}

void StatusStructure::add_line(Line* line) {
    lines_.insert(find_higher(line->get_a()), line);
}

void StatusStructure::remove_line(Line* line) {
    lines_.erase(find_closest(line));
}

void StatusStructure::swap(Line* l1, Line* l2) {
    std::swap(**find_closest(l1), **find_closest(l2));
}

void StatusStructure::print(std::ostream& os) const {
    for (auto line : lines_)
        os << *line << std::endl;
}

std::vector<Line*>::iterator StatusStructure::find_higher(Point const& query_point) {
    OrientationChecker const checker;

    if (lines_.size() == 0) {
        return lines_.begin();
    } else if (lines_.size() == 1) {
        if (checker.check({query_point, lines_[0]->get_a(), lines_[0]->get_b()}) == 1)
            return lines_.begin();
        return lines_.end();
    } else {
        int first_index(0), last_index(lines_.size()), current_index(0);

        while(true) {
            current_index = first_index + (last_index - first_index)/2;

            if (checker.check({query_point, lines_[current_index]->get_a(), lines_[current_index]->get_b()}) == 1) {
                if (current_index == first_index)
                    return lines_.begin();
                last_index = current_index;
            }
            else {
                if (current_index + 1 == last_index)
                    return lines_.begin() + last_index;
                first_index = current_index;
            }
        }

    }

}

std::vector<Line*>::iterator StatusStructure::find_closest(Line* line) {
    auto closest = find_higher(line->get_a());
    int close_pos(closest - lines_.begin());
    int i(0);

    while(i < int(lines_.size())) {

        if (close_pos + i < int(lines_.size()) && lines_[close_pos + i] == line) {
            closest = lines_.begin() + close_pos + i;
            break;

        } else if (close_pos - i >= 0 && lines_[close_pos - i] == line) {
            closest = lines_.begin() + close_pos - i;
            break;
        }

        ++i;
    }

    return closest;
}


}

std::ostream& operator<< (std::ostream& os, SIRR::StatusStructure const& status_structure) {
    status_structure.print(os);
    return os;
}
