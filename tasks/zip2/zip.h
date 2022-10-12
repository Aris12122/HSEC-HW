#pragma once

#include <iterator>

template <typename Sequence1, typename Sequence2>
class Zipped {
public:
    template <typename Iterator1, typename Iterator2>
    class ZipIterator {
    public:

        ZipIterator(Iterator1 it_a,Iterator2 it_b): it_a_(it_a), it_b_(it_b) {
        }

        auto operator*() const {
            return std::make_pair(*it_a_, *it_b_);
        }

        auto* operator->() const {
            return std::make_pair(it_a_, it_b_);
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
        Iterator1 it_a_;
        Iterator2 it_b_;
    };

    Zipped(const Sequence1& sequence1, const Sequence2& sequence2): a_(sequence1), b_(sequence2) {
    }

    const auto begin() const {
        return ZipIterator<decltype(std::begin(a_)), decltype(std::begin(b_))>(std::begin(a_), std::begin(b_));
    }

    const auto end() const {
        return ZipIterator<decltype(std::end(a_)), decltype(std::end(b_))>(std::end(a_), std::end(b_));
    }

private:
    const Sequence1& a_;
    const Sequence2& b_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(sequence1, sequence2);
}
