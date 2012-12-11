#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include <iostream>
#include <algorithm>

#include "primitives/BoundingBox.hpp"
#include "algorithms/ShapeChecker.hpp"

namespace SIRR {


template <unsigned dim>
class KDTree {

    public:
        KDTree():
            root_(NULL) {}

        void build(std::list<Point<dim>> const& points) {
            std::vector<Point<dim>> start(points.begin(), points.end());
            COMPARE_POINTS_LESS<dim> comparator(0);
            std::sort(start.begin(), start.end(), comparator);
            root_ = build(start, 0);
        }

        std::list<Point<dim>> const search(TestingShape<dim>* range) const {
            return search(root_, range);
        }

        unsigned count(TestingShape<dim>* range) const {
            return search(root_, range).size();
        }

        std::list<BoundingBox<dim>*> const get_bounding_boxes() const {
            return get_bounding_boxes(root_);
        }

        void print(std::ostream& os) const {
            auto points(report_subtree(root_));
            for (auto point : points)
                os << point << std::endl;
        }

    private:

        class KDNode {
            public:
                KDNode(Point<dim> const& position):
                    position_(position),
                    left_child_(NULL),
                    right_child_(NULL),
                    is_leaf_(true),
                    splitting_dimension_(0),
                    splitting_position_(0.f),
                    bounds_(NULL) {}

                KDNode(KDNode* left_child, KDNode* right_child,
                       unsigned splitting_dimension, float splitting_position,
                       BoundingBox<dim>* bounds):
                    position_(),
                    left_child_(left_child),
                    right_child_(right_child),
                    is_leaf_(false),
                    splitting_dimension_(splitting_dimension),
                    splitting_position_(splitting_position),
                    bounds_(bounds) {}

                Point<dim> const& get_position() const {
                    return position_;
                }

                bool is_leaf() const {
                    return is_leaf_;
                }

                KDNode* get_left_child() const {
                    return left_child_;
                }

                KDNode* get_right_child() const {
                    return right_child_;
                }

                BoundingBox<dim>* get_bounds() const {
                    return bounds_;
                }

            private:
                Point<dim> position_;
                KDNode *left_child_, *right_child_;
                bool is_leaf_;
                unsigned splitting_dimension_;
                float splitting_position_;
                BoundingBox<dim>* bounds_;

        };

        KDNode* root_;

    private:

        KDNode* build(std::vector<Point<dim>> const& points, unsigned const depth) {

            if (points.size() == 1) {
                return new KDNode(*points.begin());
            }

            auto median_position(points.begin());
            std::advance(median_position, points.size()/2);

            std::vector<Point<dim>> p1(points.begin(), median_position);
            std::vector<Point<dim>> p2(median_position, points.end());

            COMPARE_POINTS_LESS<dim> comp((depth+1) % dim);
            std::sort(p1.begin(), p1.end(), comp);
            std::sort(p2.begin(), p2.end(), comp);

            KDNode* v1(build(p1, depth + 1));
            KDNode* v2(build(p2, depth + 1));

            BoundingBox<dim>* bounds(new BoundingBox<dim>(points));

            return new KDNode(v1, v2, depth % dim, median_position->get(depth % dim), bounds);
        }

        std::list<Point<dim>> const search(KDNode* root, TestingShape<dim>* range) const {

            std::list<Point<dim>> result;
            if (root->is_leaf()) {
                if (range->contains(root->get_position())) {
                    result.push_back(root->get_position());
                }
                return result;
            }

            if (root->get_left_child()) {
                if (root->get_left_child()->is_leaf()) {
                    auto sub_result(search(root->get_left_child(), range));
                    result.insert(result.end(), sub_result.begin(), sub_result.end());
                }
                else {
                    ShapeChecker<dim> checker;
                    if (checker.is_inside(root->get_left_child()->get_bounds(), range)) {
                        auto sub_result(report_subtree(root->get_left_child()));
                        result.insert(result.end(), sub_result.begin(), sub_result.end());
                    }
                    else if (checker.intersects(root->get_left_child()->get_bounds(), range)) {
                        auto sub_result(search(root->get_left_child(), range));
                        result.insert(result.end(), sub_result.begin(), sub_result.end());
                    }
                }
            }

            if (root->get_right_child()) {
                if (root->get_right_child()->is_leaf()) {
                    auto sub_result(search(root->get_right_child(), range));
                    result.insert(result.end(), sub_result.begin(), sub_result.end());
                }
                else {
                    ShapeChecker<dim> checker;
                    if (checker.is_inside(root->get_right_child()->get_bounds(), range)) {
                        auto sub_result(report_subtree(root->get_right_child()));
                        result.insert(result.end(), sub_result.begin(), sub_result.end());
                    }
                    else if (checker.intersects(root->get_right_child()->get_bounds(), range)) {
                        auto sub_result(search(root->get_right_child(), range));
                        result.insert(result.end(), sub_result.begin(), sub_result.end());
                    }
                }
            }

            return result;
        }

        std::list<Point<dim>> const report_subtree(KDNode* root) const {
            if (root->is_leaf())
                return {root->get_position()};

            std::list<Point<dim>> left_points;
            if (root->get_left_child())
                left_points = report_subtree(root->get_left_child());

            std::list<Point<dim>> right_points;
            if (root->get_right_child())
                right_points = report_subtree(root->get_right_child());

            left_points.insert(left_points.end(), right_points.begin(), right_points.end());

            return left_points;
        }

        std::list<BoundingBox<dim>*> const get_bounding_boxes(KDNode* root) const {
            if (root->is_leaf())
                return std::list<BoundingBox<dim>*>();

            std::list<BoundingBox<dim>*> left_boxes;
            if (root->get_left_child())
                left_boxes = get_bounding_boxes(root->get_left_child());

            std::list<BoundingBox<dim>*> right_boxes;
            if (root->get_right_child())
                right_boxes = get_bounding_boxes(root->get_right_child());

            std::list<BoundingBox<dim>*> result({root->get_bounds()});

            result.insert(result.end(), left_boxes.begin(), left_boxes.end());
            result.insert(result.end(), right_boxes.begin(), right_boxes.end());

            return result;
        }
};

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::KDTree<dim> const& tree) {
    tree.print(os);
    return os;
}

#endif //KD_TREE_HPP

