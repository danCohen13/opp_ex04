#include "Board.h"
#include <stdexcept>

void Board::addBulb(const HexPosition& position, const Bulb& bulb) {
    m_bulbs.insert({ position, bulb });

    size_t graphId = m_graph.addVertex(position);
    m_positionToGraphId[position] = graphId;
    m_graphIdToPosition[graphId] = position;

    // Explicitly cache the simulation root vertex ID
    if (bulb.isCentral()) {
        m_centralVertexId = graphId;
    }
}

void Board::addConnection(const HexPosition& from, const HexPosition& to) {
    size_t fromId = m_positionToGraphId.at(from);
    size_t toId = m_positionToGraphId.at(to);
    m_graph.addEdge(fromId, toId);
}

Bulb& Board::getBulb(const HexPosition& position) {
    return m_bulbs.at(position);
}

const Bulb& Board::getBulb(const HexPosition& position) const {
    return m_bulbs.at(position);
}

Graph<HexPosition>& Board::getGraph() {
    return m_graph;
}

const Graph<HexPosition>& Board::getGraph() const {
    return m_graph;
}

size_t Board::getCentralVertexId() const {
    return m_centralVertexId;
}

HexPosition Board::getPositionFromId(size_t graphId) const {
    return m_graphIdToPosition.at(graphId);
}

const std::map<HexPosition, Bulb>& Board::getAllBulbs() const {
    return m_bulbs;
}

void Board::clear() {
    m_bulbs.clear();
    m_positionToGraphId.clear();
    m_graphIdToPosition.clear();
    m_graph.clear();
    m_centralVertexId = 0;
}

size_t Board::getIdFromPosition(const HexPosition& position) const {
    return m_positionToGraphId.at(position);
}