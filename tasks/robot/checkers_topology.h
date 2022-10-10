#pragma once

#include "topology.h"
#include <unordered_set>

class CheckersTopology : public Topology {
public:
    CheckersTopology(const std::vector<std::vector<bool>>&);

    std::vector<Point> GetAllNeighbours(const Point& point) const override;

private:
    void Dfs(const Point& point, std::unordered_set<Point>& visited) const;
};