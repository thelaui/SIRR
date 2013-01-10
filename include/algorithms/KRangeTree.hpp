#ifndef K_RANGE_TREE_HPP
#define K_RANGE_TREE_HPP

#include <iostream>
#include <algorithm>

namespace SIRR {

template <unsigned point_dim>
class KRangeTree {

    public:
        KRangeTree():
            root_(NULL) {}

        template <unsigned tree_dim>
        void generate(std::list<Point<point_dim>> const& points) {
                generate<tree_dim>(std::vector<Point<point_dim>>(points.begin(), points.end()));
        }

        template <unsigned tree_dim>
        void generate(std::vector<Point<point_dim>> const& points) {
                std::vector<Point<point_dim>> start(points.begin(), points.end());
                COMPARE_POINTS_LESS<point_dim> comparator(0);
                std::sort(start.begin(), start.end(), comparator);
                root_ = build<tree_dim>(start);
        }

        void print(std::ostream& os) const {
            auto points(report_subtree(root_));
            for (auto point : points)
                os << point << std::endl;
        }

    private:

        class KRangeNode {
            public:
                KRangeNode(Point<point_dim> const& position):
                    is_leaf_(true),
                    position_(position),
                    left_child_(NULL),
                    right_child_(NULL),
                    split_value_(0.f),
                    sub_range_tree_(NULL) {}

                KRangeNode(KRangeNode* left_child, KRangeNode* right_child,
                           float split_value,
                           KRangeTree<point_dim>* sub_range_tree):
                    is_leaf_(false),
                    position_(),
                    left_child_(left_child),
                    right_child_(right_child),
                    split_value_(split_value),
                    sub_range_tree_(sub_range_tree) {}

                Point<point_dim> const& get_position() const {
                    return position_;
                }

                bool is_leaf() const {
                    return is_leaf_;
                }

                KRangeNode* get_left_child() const {
                    return left_child_;
                }

                KRangeNode* get_right_child() const {
                    return right_child_;
                }

            private:
                bool is_leaf_;
                Point<point_dim> position_;
                KRangeNode *left_child_, *right_child_;
                float split_value_;
                KRangeTree<point_dim>* sub_range_tree_;
        };

        KRangeNode* root_;

    private:

        template <unsigned tree_dim>
        KRangeNode* build(std::vector<Point<point_dim>> const& points) {
            if (points.size() == 1) {
                return new KRangeNode(points[0]);
            }

            auto median_position(points.begin());
            std::advance(median_position, points.size()/2);

            std::vector<Point<point_dim>> left_points(points.begin(), median_position);
            std::vector<Point<point_dim>> right_points(median_position, points.end());

            KRangeNode* left_child(build<tree_dim>(left_points));
            KRangeNode* right_child(build<tree_dim>(right_points));
            KRangeTree<point_dim>* sub_range_tree(new KRangeTree<point_dim>());
            sub_range_tree->generate<tree_dim-1>(points);

            return new KRangeNode(left_child, right_child, median_position->get(point_dim - tree_dim), sub_range_tree);
        }

        std::list<Point<point_dim>> const report_subtree(KRangeNode* root) const {
            if (root->is_leaf())
                return {root->get_position()};

            std::list<Point<point_dim>> left_points;
            if (root->get_left_child())
                left_points = report_subtree(root->get_left_child());

            std::list<Point<point_dim>> right_points;
            if (root->get_right_child())
                right_points = report_subtree(root->get_right_child());

            left_points.insert(left_points.end(), right_points.begin(), right_points.end());

            return left_points;
        }

};

template <>
template <>
void KRangeTree<1>::generate<0>(std::list<Point<1>> const& points) {

}

template <>
template <>
void KRangeTree<1>::generate<0>(std::vector<Point<1>> const& points) {

}

template <>
template <>
KRangeTree<1>::KRangeNode* KRangeTree<1>::build<0>(std::vector<Point<1>> const& points) {
    return NULL;
}

}

template <unsigned point_dim>
std::ostream& operator<< (std::ostream& os, SIRR::KRangeTree<point_dim> const& tree) {
    tree.print(os);
    return os;
}

#endif //K_RANGE_TREE_HPP


