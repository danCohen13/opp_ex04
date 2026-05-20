#include "LightPropagationSystem.h"
#include "ConnectionValidator.h"
#include "HexGeometry.h"
#include <map>
#include <set>

static void dfs(Board& board,
    const HexPosition& current,
    std::set<HexPosition>& visited)
{
    visited.insert(current);
    board.getBulb(current).setLitState(true);

    std::vector<HexPosition> neighbors = HexGeometry::getNeighbors(current);
    const auto& allBulbs = board.getAllBulbs();

    for (size_t i = 0; i < 6; ++i)
    {
        const HexPosition& neighborPos = neighbors[i];
        Direction dir = static_cast<Direction>(i);

        if (allBulbs.find(neighborPos) == allBulbs.end()) continue;

        if (visited.count(neighborPos)) continue;

        if (ConnectionValidator::canConnect(board, current, neighborPos, dir))
        {
            dfs(board, neighborPos, visited);
        }
    }
}

void LightPropagationSystem::updatePropagation(Board& board)
{
    for (auto& pair : const_cast<std::map<HexPosition, Bulb>&>(board.getAllBulbs()))
    {
        pair.second.setLitState(false);
    }

    HexPosition rootPos = board.getPositionFromId(board.getCentralVertexId());
    std::set<HexPosition> visited;
    dfs(board, rootPos, visited);
}