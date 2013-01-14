#ifndef K_RANGE_TREE_SPEC_INL
#define K_RANGE_TREE_SPEC_INL

namespace SIRR {

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

template <>
template <>
std::list<Point<1>> const KRangeTree<1>::range_search<0>(BoundingBox<1> const& bbox) const {
    return {};
}

template <>
template <>
void KRangeTree<2>::generate<0>(std::list<Point<2>> const& points) {

}

template <>
template <>
void KRangeTree<2>::generate<0>(std::vector<Point<2>> const& points) {

}

template <>
template <>
KRangeTree<2>::KRangeNode* KRangeTree<2>::build<0>(std::vector<Point<2>> const& points) {
    return NULL;
}

template <>
template <>
std::list<Point<2>> const KRangeTree<2>::range_search<0>(BoundingBox<2> const& bbox) const {
    return {};
}


template <>
template <>
void KRangeTree<3>::generate<0>(std::list<Point<3>> const& points) {

}

template <>
template <>
void KRangeTree<3>::generate<0>(std::vector<Point<3>> const& points) {

}

template <>
template <>
KRangeTree<3>::KRangeNode* KRangeTree<3>::build<0>(std::vector<Point<3>> const& points) {
    return NULL;
}

template <>
template <>
void KRangeTree<3>::print<0>(std::ostream& os) const {

}

template <>
template <>
void KRangeTree<2>::print<0>(std::ostream& os) const {

}

template <>
template <>
void KRangeTree<1>::print<0>(std::ostream& os) const {

}

}

#endif //K_RANGE_TREE_SPEC_INL
