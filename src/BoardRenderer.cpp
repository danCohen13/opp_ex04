#include "BoardRenderer.h"
#include "BulbRenderer.h"
#include <cmath>

BoardRenderer::BoardRenderer(const Board& board, ResourceManager& resourceManager)
    : m_board(board), m_resourceManager(resourceManager) {
}

sf::Vector2f BoardRenderer::hexToPixel(const HexPosition& position) const {
    float x = m_hexRadius * (std::sqrt(3.0f) * position.q + std::sqrt(3.0f) / 2.0f * position.r);
    float y = m_hexRadius * (3.0f / 2.0f * position.r);

    return { x + 400.0f, y + 250.0f };
}

void BoardRenderer::render(sf::RenderTarget& target) {
    for (const auto& pair : m_board.getAllBulbs()) {
        HexPosition pos = pair.first;

        BulbRenderer bulbRender(pair.second, m_resourceManager);
        bulbRender.update();
        bulbRender.setPosition(hexToPixel(pos));

        target.draw(bulbRender);
    }
}

bool BoardRenderer::isTileClicked(const HexPosition& position, const sf::Vector2i& mousePos) const {
    sf::Vector2f tileCenter = hexToPixel(position);

    float deltaX = mousePos.x - tileCenter.x;
    float deltaY = mousePos.y - tileCenter.y;
    float distanceSquared = (deltaX * deltaX) + (deltaY * deltaY);

    return distanceSquared <= (m_hexRadius * m_hexRadius);
}