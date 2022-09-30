#include "word2vec.h"

#include <vector>

int64_t ScalarProduct(const std::vector<int>& v1, const std::vector<int>& v2) {
    int64_t scalar_product = 0;
    for (std::size_t i = 0; i < v1.size(); ++i) {
        scalar_product += static_cast<int64_t>(v1[i]) * static_cast<int64_t>(v2[i]);
    }
    return scalar_product;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {

    std::vector<std::string> closest_words;
    int64_t max_scalar_product = INT64_MIN;
    for (std::size_t i = 1; i < words.size(); ++i) {
        int64_t scalar_product = ScalarProduct(vectors[0], vectors[i]);
        if (scalar_product < max_scalar_product) {
            continue;
        } else if (scalar_product > max_scalar_product) {
            max_scalar_product = scalar_product;
            closest_words.clear();
        }
        closest_words.emplace_back(words[i]);
    }
    return closest_words;
}
