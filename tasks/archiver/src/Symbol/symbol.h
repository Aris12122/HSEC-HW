//
// Created by aris on 10/20/22.
//
#pragma once

#include <vector>
#include <string>

class Symbol{
public:
    Symbol();
    explicit Symbol(size_t x);
    explicit Symbol(const std::vector<bool>& vb);
    explicit Symbol(const std::string& b_str);

    bool operator<(const Symbol& other) const;

    bool operator!=(const Symbol& other) const;

    bool operator==(const Symbol& other) const;

    Symbol& operator++();

    size_t Size() const;

    bool IsEmpty() const;

    void Add(bool x);

    bool operator[](size_t pos) const;

    std::vector<bool> bit_seq_;
};

template<>
struct std::hash<Symbol>{
    size_t operator()(const Symbol& symbol) const{
        return std::hash<std::vector<bool>>{}(symbol.bit_seq_);
    }
};

std::vector<Symbol> TransformString(const std::string& str);

std::vector<Symbol> TransformFileName(const std::string& file_name);
