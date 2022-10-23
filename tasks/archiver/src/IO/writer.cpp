//
// Created by aris on 10/21/22.
//
#include "writer.h"

Writer::Writer(std::ostream& output) : output_(output), len_(BUFFER_SIZE) {
}
void Writer::WriteSymbol(const Symbol& symbol) {
    for (size_t i = 0; i < symbol.Size(); ++i) {
        WriteBit(symbol[i]);
    }
}
void Writer::WriteBit(bool x) {
    buff_[--len_] = x;
    if (len_ == 0u) {
        Print();
    }
}
Writer::~Writer() {
    Flush();
}
void Writer::Print() {
    int out = 0;
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        out |= buff_[i] << i;
    }
    output_ << static_cast<char>(out);
    buff_.reset();
    len_ = BUFFER_SIZE;
}
void Writer::Flush() {
    if (len_ < BUFFER_SIZE) {
        Print();
    }
}
