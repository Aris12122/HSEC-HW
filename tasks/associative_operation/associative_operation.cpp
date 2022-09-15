#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    size_t n = table.size();

    for (size_t x = 0; x < n; ++x) {
        for (size_t y = 0; y < n; ++y) {
            for (size_t z = 0; z < n; ++z) {
                size_t xy = table[x][y];
                size_t yz = table[y][z];

                size_t xy_z = table[xy][z];
                size_t x_yz = table[x][yz];

                if (xy_z != x_yz) {
                    return false;
                }
            }
        }
    }
    return true;
}
