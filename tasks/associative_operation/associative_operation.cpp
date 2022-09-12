#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    if (table.empty()) {
        return true;
    }

    size_t n = table.size();
    if (table[0].size() != n) {
        return false;
    }

    for (size_t x = 0; x < n; ++x) {
        for (size_t y = 0; y < n; ++y) {
            for (size_t z = 0; z < n; ++z) {
                size_t left = table[x][y];
                size_t right = table[y][z];

                if (left >= n || right >= n) {
                    return false;
                }
                left = table[left][z];
                right = table[x][right];

                if (left != right) {
                    return false;
                }
            }
        }
    }
    return true;
}
