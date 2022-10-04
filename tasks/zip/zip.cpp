#include "zip.h"

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    Zipped zipped;
    for (; a_begin != a_end && b_begin != b_end; ++a_begin, ++b_begin) {
        zipped.zipped_list_.emplace_back(*a_begin, *b_begin);
    }
    return zipped;
}

const std::_List_const_iterator<ZippedPair> Zipped::begin() const {
    return zipped_list_.begin();
}

const std::_List_const_iterator<ZippedPair> Zipped::end() const {
    return zipped_list_.end();
}