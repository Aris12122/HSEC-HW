//
// Created by aris on 10/21/22.
//
#include "reader.h"

Reader::Reader(std::istream& input): input_(input) {
    buff_ = 0;
    cur_pos_ = BUFFER_SIZE;
}

void Reader::ReadSymbol(Symbol& symbol, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        symbol.bit_seq_.emplace_back(ReadBit());
    }
}
bool Reader::ReadBit() {
    if (cur_pos_ == BUFFER_SIZE) {
        buff_ = 0;
        input_.read(&buff_, BUFFER_SIZE);
        cur_pos_ = 0u;
    }
    return (buff_ >> cur_pos_++) & 1;
}
