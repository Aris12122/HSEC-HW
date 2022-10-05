#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class ZipIterator {
public:
    ZipIterator(Iterator it_a,Iterator it_b);

    ZippedPair operator*() const {
        return ZippedPair{*it_a_, *it_b_};
    }

    ZipIterator& operator++() {
        ++it_a_;
        ++it_b_;
        return *this;
    }

    bool operator!=(ZipIterator& other) const {
        return it_a_ != other.it_a_ && it_b_ != other.it_b_;
    }
private:
    Iterator it_a_;
    Iterator it_b_;
};

class Zipped {
public:
    Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);

    const ZipIterator begin() const;

    const ZipIterator end() const;

    friend Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);

private:
    const Iterator a_begin_;
    const Iterator a_end_;

    const Iterator b_begin_;
    const Iterator b_end_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
