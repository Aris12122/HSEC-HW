#include "zip.h"

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    return Zipped(a_begin, a_end, b_begin, b_end);
}
Zipped::Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end):
      a_begin_(a_begin), a_end_(a_end), b_begin_(b_begin), b_end_(b_end) {
}
const ZipIterator Zipped::begin() const {
    return ZipIterator(a_begin_, b_begin_);
}
const ZipIterator Zipped::end() const {
    return ZipIterator(a_end_, b_end_);
}
ZipIterator::ZipIterator(Iterator it_a, Iterator it_b): it_a_(it_a), it_b_(it_b) {
}
