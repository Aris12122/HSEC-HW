//
// Created by aris on 10/21/22.
//
#include "writer.h"

Writer::Writer(std::ostream& output): output_(output), len_(0u) {
}
void Writer::WriteSymbol(Symbol& symbol) {
    for (size_t i = 0; i < symbol.Size(); ++i) {
        WriteBit(symbol[i]);
    }
}
void Writer::WriteBit(bool x) {
    buff_[len_++] = x;
    if (len_ == BUFFER_SIZE) {
        Print();
    }
}
Writer::~Writer() {
    Flush();
}
void Writer::Print() {
    output_ << buff_.to_string().substr(BUFFER_SIZE - len_, len_);
    buff_.reset();
    len_ = 0u;
}
void Writer::Flush() {
    if (len_ > 0) {
        Print();
    }
}
