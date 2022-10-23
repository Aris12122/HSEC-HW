//
// Created by aris on 10/20/22.
//
#pragma once
#include "huffman.h"
#include "../IO/reader.h"
#include "../IO/writer.h"
#include "../init.h"
#include <memory>


class Encoder : public Huffman{
public:
    Encoder();

    void Add(const Symbol& symbol);
    void Add(const std::vector<Symbol>& symbols);
    void Add(Reader& reader);

    void Encode();

    void PrintEncoded(Reader& reader, Writer& writer);
    void PrintEncoded(const Symbol& symbol, Writer& writer);
    void PrintEncoded(const std::vector<Symbol>& symbols, Writer& writer);

    void PrintTrieData(Writer& writer);

private:
    void ToCanonical();

    void GetLeafs(std::unique_ptr<Trie>& vertex, std::vector<std::pair<size_t, Symbol>>& len_symbol_vec, size_t len = 0);

    std::unordered_map<Symbol, size_t> frequency_;
    std::unordered_map<Symbol, Symbol> coded_symbol_;
    std::unordered_map<size_t, size_t> num_code_size_;
    std::vector<Symbol> ordered_symbols_;

    size_t max_code_size_ = 0u;
    size_t symbols_count_ = 0u;
};
