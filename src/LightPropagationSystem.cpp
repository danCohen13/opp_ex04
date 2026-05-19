#include "LightPropagationSystem.h"
#include "ConnectionValidator.h"
#include "HexGeometry.h"
#include <map>
#include <vector>
#include <queue>

void LightPropagationSystem::updatePropagation(Board& board) {
    auto& graph = board.getGraph();
    size_t vertexCount = graph.getVertexCount();

    if (vertexCount == 0) {
        return;
    }

    // Step 1: Reset lit state for all bulbs
    for (auto& pair : const_cast<std::map<HexPosition, Bulb>&>(board.getAllBulbs())) {
        pair.second.setLitState(false);
    }

    std::vector<bool> visited(vertexCount, false);
    std::queue<size_t> queue;

    // Step 2: Initialize BFS with the central power source vertex
    size_t rootId = board.getCentralVertexId();
    HexPosition rootPos = board.getPositionFromId(rootId);
    board.getBulb(rootPos).setLitState(true);
    visited[rootId] = true;
    queue.push(rootId);

    // Step 3: Standard Breadth-First Search loop
    while (!queue.empty()) {
        size_t currentId = queue.front();
        queue.pop();

        HexPosition currentPos = board.getPositionFromId(currentId);
        std::vector<HexPosition> neighbors = HexGeometry::getNeighbors(currentPos);

        for (size_t i = 0; i < 6; ++i) {
            HexPosition neighborPos = neighbors[i];
            Direction dir = static_cast<Direction>(i);

            const auto& allBulbs = board.getAllBulbs();
            if (allBulbs.find(neighborPos) != allBulbs.end()) {

                if (ConnectionValidator::canConnect(board, currentPos, neighborPos, dir)) {
                    const std::vector<size_t>& graphNeighbors = graph.getNeighbors(currentId);

                    for (size_t neighborId : graphNeighbors) {
                        HexPosition checkPos = board.getPositionFromId(neighborId);

                        if (checkPos == neighborPos && !visited[neighborId]) {
                            visited[neighborId] = true;
                            board.getBulb(neighborPos).setLitState(true);
                            queue.push(neighborId);
                        }
                    }
                }
            }
        }
    }
}