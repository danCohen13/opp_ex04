#pragma once

#include "HexPosition.h"
#include "Bulb.h"
#include "Graph.h"
#include <map>
#include <vector>
#include <cstddef>

class Board {
public:
    Board() = default;
    ~Board() = default;

    void addBulb(const HexPosition& position, const Bulb& bulb);
    void addConnection(const HexPosition& from, const HexPosition& to);

    Bulb& getBulb(const HexPosition& position);
    const Bulb& getBulb(const HexPosition& position) const;

    Graph<HexPosition>& getGraph();
    const Graph<HexPosition>& getGraph() const;

    size_t getCentralVertexId() const;
    HexPosition getPositionFromId(size_t graphId) const;
    const std::map<HexPosition, Bulb>& getAllBulbs() const;

    void clear();

private:
    Graph<HexPosition> m_graph;
    std::map<HexPosition, Bulb> m_bulbs;
    std::map<HexPosition, size_t> m_positionToGraphId;
    std::map<size_t, HexPosition> m_graphIdToPosition;
    size_t m_centralVertexId = 0;
};