//
// Created by aris on 10/20/22.
//
#pragma once
#include "../Symbol/symbol.h"
#include "unordered_map"
#include "memory"

class Huffman{

protected:
    Huffman();

    struct Trie {
        Trie();

        explicit Trie(const Symbol& symbol);

        explicit Trie(const Symbol& symbol, Trie* l, Trie* r);

        explicit Trie(Trie* l, Trie* r);

        ~Trie();

        Symbol symbol;
        std::unique_ptr<Trie> left;
        std::unique_ptr<Trie> right;
    };
    std::unique_ptr<Trie> root;

    void BuildTrie(std::vector<std::pair<Symbol, Symbol>> symbol_code);
    bool IsLeaf(std::unique_ptr<Trie>& vertex);

    void TrieAddSymbol(std::unique_ptr<Trie>& vertex, const Symbol& code, const Symbol symbol, size_t pos = 0u);
};