#include "checkers_topology.h"
CheckersTopology::CheckersTopology(const std::vector<std::vector<bool>>& field) : Topology(field) {
}
void CheckersTopology::Dfs(const Point& point, std::unordered_set<Point>& visited) const {
    if (visited.contains(point)) {
        return;
    }
    visited.insert(point);

    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            int ix = static_cast<int>(point.x);
            int iy = static_cast<int>(point.y);
            if (!IsInField(ix + dx, iy + dy)) {
                continue;
            }
            Point cur_point = MovedPoint(point, dx, dy);
            ix = static_cast<int>(cur_point.x);
            iy = static_cast<int>(cur_point.y);
            if (!IsAvailable(cur_point)) {
                continue;
            }
            for (int tx = -1; tx <= 1; tx += 2) {
                for (int ty = -1; ty <= 1; ty += 2) {
                    if (!IsInField(ix + tx, iy + ty) || !IsAvailable(MovedPoint(cur_point, tx, ty))) {
                        continue;
                    }
                    Dfs(MovedPoint(cur_point, tx, ty), visited);
                }
            }
        }
    }
}
std::vector<Point> CheckersTopology::GetAllNeighbours(const Point& point) const {
    std::unordered_set<Point> visited;
    int ix = static_cast<int>(point.x);
    int iy = static_cast<int>(point.y);

    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            if (ix + dx < 0 || ix + dx >= GetFieldWidth() || iy + dy < 0 || iy + dy >= GetFieldHigh()) {
                continue;
            }
            visited.insert(MovedPoint(point, dx, dy));
        }
    }
    Dfs(point, visited);
    visited.erase(point);

    return std::vector<Point>(visited.begin(), visited.end());
}