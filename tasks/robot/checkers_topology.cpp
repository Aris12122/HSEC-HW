#include "checkers_topology.h"
CheckersTopology::CheckersTopology(const std::vector<std::vector<bool>>& field) : Topology(field) {
}
void CheckersTopology::Dfs(const Point& point, std::unordered_set<Point>& visited) const {
    if (visited.contains(point)) {
        return;
    }
    int ix = static_cast<int>(point.x);
    int iy = static_cast<int>(point.y);

    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            if (ix + dx < 0 || ix + dx >= GetFieldWidth() || iy + dy < 0 || iy + dy >= GetFieldHigh()) {
                continue;
            }
            Dfs(MovedPoint(point, dx, dy), visited);
        }
    }
}
std::vector<Point> CheckersTopology::GetAllNeighbours(const Point& point) const {
    std::unordered_set<Point> visited;
    Dfs(point, visited);

    return std::vector<Point>(visited.begin(), visited.end());
}