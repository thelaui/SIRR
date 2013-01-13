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

}

#endif //K_RANGE_TREE_SPEC_INL
