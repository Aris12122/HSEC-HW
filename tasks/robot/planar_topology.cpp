#include "planar_topology.h"
PlanarTopology::PlanarTopology(const std::vector<std::vector<bool>>& field) : Topology(field) {
}
std::vector<Point> PlanarTopology::GetAllNeighbours(const Point& point) const {
    std::vector<Point> result;
    int ix = static_cast<int>(point.x);
    int iy = static_cast<int>(point.y);

    for (auto [dx, dy] : dd_) {
        if (ix + dx < 0 || ix + dx >= GetFieldWidth() || iy + dy < 0 || iy + dy >= GetFieldHigh()) {
            continue;
        }
        result.emplace_back(MovedPoint(point, dx, dy));
    }

    return result;
}
