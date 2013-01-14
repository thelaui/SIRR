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
                COMPARE_POINTS_LESS<point_dim> comparator(point_dim-tree_dim);
                std::sort(start.begin(), start.end(), comparator);
                root_ = build<tree_dim>(start);
        }

        template <unsigned tree_dim>
        std::list<Point<point_dim>> const range_search(BoundingBox<point_dim> const& bbox) const {
            if (root_)
                return root_->template search<tree_dim>(bbox);
            return {};
        }

        template <unsigned tree_dim>
        void print(std::ostream& os) const {
            if (root_)
                root_->print(os, 0);
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

                KRangeTree<point_dim>* get_sub_range_tree() const {
                    return sub_range_tree_;
                }

                template <unsigned tree_dim>
                std::list<Point<point_dim>> const search(BoundingBox<point_dim> const& bbox) const {
                    if (is_leaf_) {
                        if (position_.get(point_dim-tree_dim) >= bbox.get_min().get(point_dim-tree_dim) &&
                            position_.get(point_dim-tree_dim) <= bbox.get_max().get(point_dim-tree_dim))
                            return {position_};
                        return {};
                    }

                    if (split_value_ >= bbox.get_min().get(point_dim-tree_dim) &&
                        split_value_ < bbox.get_max().get(point_dim-tree_dim)) {
                        std::list<Point<point_dim>> left_points;
                        if (left_child_)
                            left_points = left_child_->report_left_part_of_split<tree_dim>(bbox);

                        std::list<Point<point_dim>> right_points;
                        if (right_child_)
                            right_points = right_child_->report_right_part_of_split<tree_dim>(bbox);

                        left_points.insert(left_points.end(), right_points.begin(), right_points.end());

                        return left_points;
                    }

                    if (split_value_ <= bbox.get_min().get(point_dim-tree_dim))
                        if (right_child_)
                            return right_child_->search<tree_dim>(bbox);

                    if (split_value_ >= bbox.get_max().get(point_dim-tree_dim))
                        if (left_child_)
                            return left_child_->search<tree_dim>(bbox);
                    return {};
                }

                template <unsigned tree_dim>
                std::list<Point<point_dim>> const report_left_part_of_split(BoundingBox<point_dim> const& bbox) const {
                    if (is_leaf_) {
                        if (position_.get(point_dim-tree_dim) >= bbox.get_min().get(point_dim-tree_dim) && position_.get(point_dim-tree_dim) <= bbox.get_max().get(point_dim-tree_dim))
                            return {position_};
                        return {};
                    }

                    std::list<Point<point_dim>> right_points;
                    if (right_child_)
                        right_points = right_child_->report_subtree<tree_dim>(bbox);

                    std::list<Point<point_dim>> left_points;
                    if (split_value_ >= bbox.get_min().get(point_dim-tree_dim))
                        if (left_child_)
                            left_points = left_child_->report_left_part_of_split<tree_dim>(bbox);

                    left_points.insert(left_points.end(), right_points.begin(), right_points.end());
                    return left_points;
                }

                template <unsigned tree_dim>
                std::list<Point<point_dim>> const report_right_part_of_split(BoundingBox<point_dim> const& bbox) const {
                    if (is_leaf_) {
                        if (position_.get(point_dim-tree_dim) >= bbox.get_min().get(point_dim-tree_dim) && position_.get(point_dim-tree_dim) <= bbox.get_max().get(point_dim-tree_dim))
                            return {position_};
                        return {};
                    }

                    std::list<Point<point_dim>> left_points;
                    if (left_child_)
                        left_points = left_child_->report_subtree<tree_dim>(bbox);

                    std::list<Point<point_dim>> right_points;
                    if (split_value_ <= bbox.get_max().get(point_dim-tree_dim))
                        if (right_child_)
                            right_points = right_child_->report_right_part_of_split<tree_dim>(bbox);

                    left_points.insert(left_points.end(), right_points.begin(), right_points.end());
                    return left_points;
                }

                template <unsigned tree_dim>
                std::list<Point<point_dim>> const report_subtree(BoundingBox<point_dim> const& bbox) const {

                    if (is_leaf_) {
                        if (tree_dim == 1)
                            return {position_};
                        return {};
                    }

                    std::list<Point<point_dim>> central_points;
                    if (sub_range_tree_)
                        central_points = sub_range_tree_->range_search<tree_dim>(bbox);

                    std::list<Point<point_dim>> left_points;
                    if (left_child_)
                        left_points = left_child_->report_subtree<tree_dim>(bbox);

                    std::list<Point<point_dim>> right_points;
                    if (right_child_)
                        right_points = right_child_->report_subtree<tree_dim>(bbox);

                    left_points.insert(left_points.end(), central_points.begin(), central_points.end());
                    left_points.insert(left_points.end(), right_points.begin(), right_points.end());

                    return left_points;

                }


                void print(std::ostream& os, unsigned depth) const {
                    for (unsigned i(0); i<depth; ++i)
                        os << " ";

                    if (is_leaf_)
                        os << "leaf\t" << position_;
                    else
                        os << "intern\t" << split_value_;

                    os << std::endl;

                    if (left_child_)
                        left_child_->print(os, depth+1);
                    if (right_child_)
                        right_child_->print(os, depth+1);
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
            std::advance(median_position, int(float(points.size())/2.0 + 0.5));

            std::vector<Point<point_dim>> left_points(points.begin(), median_position);
            std::vector<Point<point_dim>> right_points(median_position, points.end());

            KRangeNode* left_child(build<tree_dim>(left_points));
            KRangeNode* right_child(build<tree_dim>(right_points));
            KRangeTree<point_dim>* sub_range_tree(new KRangeTree<point_dim>());
            sub_range_tree->generate<tree_dim-1>(points);

            return new KRangeNode(left_child, right_child, (median_position-1)->get(point_dim - tree_dim), sub_range_tree);
        }

};

}

#include "algorithms/KRangeTree.spec.inl"

template <unsigned point_dim, unsigned tree_dim = 1>
std::ostream& operator<< (std::ostream& os, SIRR::KRangeTree<point_dim> const& tree) {
    tree.template print<tree_dim>(os);
    return os;
}

#endif //K_RANGE_TREE_HPP


