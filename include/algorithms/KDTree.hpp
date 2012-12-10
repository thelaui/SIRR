#ifndef KD_NODE_HPP
#define KD_NODE_HPP

#include <iostream>

#include "primitives/BoundingBox.hpp"

namespace SIRR {


template <unsigned dim>
class KDTree {

    public:
        KDTree():
            root_(NULL) {}

        void build(std::list<Point<dim>> const& points) {
            COMPARE_POINTS_LESS<dim> comparator(0);
            std::multiset<Point<dim>, COMPARE_POINTS_LESS<dim>> start(comparator);
            start.insert(points.begin(), points.end());
            root_ = build(start, 0);
        }

        std::list<Point<dim>> const search(BoundingBox<dim> const& range) const;

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
                    bounds_() {}

                KDNode(KDNode* left_child, KDNode* right_child,
                       unsigned splitting_dimension, float splitting_position,
                       BoundingBox<dim> const& bounds):
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

            private:
                Point<dim> position_;
                KDNode *left_child_, *right_child_;
                bool is_leaf_;
                unsigned splitting_dimension_;
                float splitting_position_;
                BoundingBox<dim> bounds_;

        };

        KDNode* build(std::multiset<Point<dim>, COMPARE_POINTS_LESS<dim>> const& points, unsigned const depth) {

//            for (auto point : points) {
//                for (unsigned i(0); i < depth; ++i)
//                    std::cout << "   ";
//                std::cout << point << std::endl;
//            }

            if (points.size() == 1) {
                return new KDNode(*points.begin());
            }

            auto median_position(points.begin());
            std::advance(median_position, points.size()/2);
//            std::cout << "----" << *median_position << std::endl;
            COMPARE_POINTS_LESS<dim> comp(depth % dim);
            std::multiset<Point<dim>, COMPARE_POINTS_LESS<dim>> p1(points.begin(), median_position, comp);
            std::multiset<Point<dim>, COMPARE_POINTS_LESS<dim>> p2(median_position, points.end(), comp);

            KDNode* v1(build(p1, depth + 1));
            KDNode* v2(build(p2, depth + 1));

            BoundingBox<dim> bounds(points);
            return new KDNode(v1, v2, depth%dim, median_position->get(depth%dim), bounds);
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

        KDNode* root_;

};

}

template <unsigned dim>
std::ostream& operator<< (std::ostream& os, SIRR::KDTree<dim> const& tree) {
    tree.print(os);
    return os;
}

#endif //KD_NODE_HPP

