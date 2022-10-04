#pragma once

#include <forward_list>
#include <string>
#include <list>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
public:
    const std::_List_const_iterator<ZippedPair> begin() const;

    const std::_List_const_iterator<ZippedPair> end() const;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
