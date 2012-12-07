#include "algorithms/StatusStructure.hpp"

#include "algorithms/StartEvent.hpp"
#include "algorithms/EndEvent.hpp"
#include "algorithms/IntersectionEvent.hpp"
#include "primitives/Line.hpp"

#include <iostream>

namespace SIRR {

StatusStructure::StatusStructure():
    lines_() {}

Point3D const StatusStructure::process_event(Event* event, EventStructure& event_structure) {
    Point3D result(0.f, 0.f, -1.f);
    Event::EventType type(event->get_type());

    switch (type) {
        case Event::START: {
            StartEvent* start_event(reinterpret_cast<StartEvent*>(event));
            //std::cout << "Processing " << *start_event << std::endl;
            add_line(start_event, event_structure);
        } break;

        case Event::END: {
            EndEvent* end_event(reinterpret_cast<EndEvent*>(event));
            //std::cout << "Processing " << *end_event << std::endl;
            remove_line(end_event, event_structure);
        } break;

        case Event::INTERSECTION: {
            IntersectionEvent* intersection_event(reinterpret_cast<IntersectionEvent*>(event));
            //std::cout << "Processing " << *intersection_event << std::endl;
            swap(intersection_event, event_structure);
            result = intersection_event->get_position();
        } break;

        default: break;

    }
//    std::cout << std::endl;

    return result;
}

void StatusStructure::print(std::ostream& os) const {
    for (auto line : lines_)
        os << *line << std::endl;
}

void StatusStructure::add_line(StartEvent* event, EventStructure& event_structure) {
    auto insert_position(find_higher(event->get_l()));

    auto intersection_right(Point3D(0.f, 0.f, -1.f));
    auto intersection_left(Point3D(0.f, 0.f, -1.f));

    if (insert_position != lines_.end()) {
        if (insert_position != lines_.end()) {
            intersection_right = event->get_l()->intersects(**insert_position);
            if (intersection_right.get_z() != -1.f)
                event_structure.add_event(new IntersectionEvent(intersection_right, event->get_l(), *insert_position));
        }
    }

    if (insert_position != lines_.begin()) {
        intersection_left = event->get_l()->intersects(**(insert_position-1));
        if (intersection_left.get_z() != -1.f)
            event_structure.add_event(new IntersectionEvent(intersection_left, *(insert_position-1), event->get_l()));
    }

    lines_.insert(insert_position, event->get_l());
}

void StatusStructure::remove_line(EndEvent* event, EventStructure& event_structure) {
    auto deletion_position(find_closest(event->get_l()));
    auto intersection(Point3D(0.f, 0.f, -1.f));

    if (deletion_position > lines_.begin() && deletion_position < lines_.end()-1) {
        intersection = (*(deletion_position - 1))->intersects(**(deletion_position+1));
        if (intersection.get_z() != -1.f && intersection.get_y() > event->get_position().get_y())
            event_structure.add_event(new IntersectionEvent(intersection, *(deletion_position - 1), *(deletion_position+1)));
    }

    lines_.erase(deletion_position);

}

void StatusStructure::swap(IntersectionEvent* event, EventStructure& event_structure) {
    auto swap_left(find_closest(event->get_l1()));
    auto swap_right(find_closest(event->get_l2()));
    auto intersection_right(Point3D(0.f, 0.f, -1.f));
    auto intersection_left(Point3D(0.f, 0.f, -1.f));

    if (swap_right < lines_.end() - 1) {
        intersection_right = event->get_l1()->intersects(**(swap_right + 1));
        if (intersection_right.get_z() != -1.f && intersection_right.get_y() >= event->get_position().get_y())
            event_structure.add_event(new IntersectionEvent(intersection_right, event->get_l1(), *(swap_right + 1)));
    }

    if (swap_left > lines_.begin()) {
        intersection_left = event->get_l2()->intersects(**(swap_left - 1));
        if (intersection_left.get_z() != -1.f && intersection_left.get_y() >= event->get_position().get_y())
            event_structure.add_event(new IntersectionEvent(intersection_left, *(swap_left - 1), event->get_l2()));
    }

    auto tmp = *swap_left;
    *swap_left = *swap_right;
    *swap_right = tmp;
}

std::vector<Line*>::iterator StatusStructure::find_higher(Line* query_line) {
    OrientationChecker const checker;

    if (lines_.size() == 0) {
        return lines_.begin();
    } else {
        int first_index(0), last_index(lines_.size()), current_index(0);

        while(true) {
            current_index = first_index + (last_index - first_index)/2;
            float orientation(checker.check({query_line->get_a(), lines_[current_index]->get_a(), lines_[current_index]->get_b()}));
            if (orientation == 1) {
                if (current_index == first_index)
                    return lines_.begin();
                last_index = current_index;
            } else if (orientation == -1) {
                if (current_index + 1 == last_index)
                    return lines_.begin() + last_index;
                first_index = current_index;
            } else {
                if (checker.check({query_line->get_b(), lines_[current_index]->get_a(), lines_[current_index]->get_b()}) == 1) {
                    if (current_index == first_index)
                        return lines_.begin();
                    last_index = current_index;
                } else {
                    if (current_index + 1 == last_index)
                        return lines_.begin() + last_index;
                    first_index = current_index;
                }
            }
        }

    }

}

std::vector<Line*>::iterator StatusStructure::find_closest(Line* line) {
    auto closest = find_higher(line);

    if (*closest != line) {
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
    }

    if (closest == lines_.end())
        return closest - 1;
    return closest;
}

}

std::ostream& operator<< (std::ostream& os, SIRR::StatusStructure const& status_structure) {
    status_structure.print(os);
    return os;
}
