#include "zip.h"

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    Iterator it_b = b_begin;
    Zipped zipped;
    for (Iterator it_a = a_begin; it_a != a_end && it_b != b_end; ++it_a, ++it_b) {
        zipped.zipped_list_.push_back(ZippedPair{*it_a, *it_b});
    }
    return zipped;
}

const std::_List_const_iterator<ZippedPair> Zipped::begin() const {
    return zipped_list_.begin();
}

const std::_List_const_iterator<ZippedPair> Zipped::end() const {
    return zipped_list_.end();
}