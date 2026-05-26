#include "BoardRenderer.h"
#include "BulbRenderer.h"
#include <cmath>

const float BOARD_OFFSET_X = 400.0f;
const float BOARD_OFFSET_Y = 250.0f;
const float HEX_WIDTH_MULTIPLIER = std::sqrt(3.0f);
const float HEX_HEIGHT_MULTIPLIER = 3.0f / 2.0f;

BoardRenderer::BoardRenderer(const Board& board, ResourceManager& resourceManager)
    : m_board(board), m_resourceManager(resourceManager) {
}

sf::Vector2f BoardRenderer::hexToPixel(const HexPosition& position) const {
    float x = m_hexRadius * (HEX_WIDTH_MULTIPLIER * position.q + (HEX_WIDTH_MULTIPLIER / 2.0f) * position.r);
    float y = m_hexRadius * (HEX_HEIGHT_MULTIPLIER * position.r);

    return { x + BOARD_OFFSET_X, y + BOARD_OFFSET_Y };
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