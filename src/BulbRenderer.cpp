#include "BulbRenderer.h"
#include <cmath>

const float HEX_BG_RADIUS = 38.0f;
const float HEX_BG_OUTLINE = 1.0f;
const float HEX_ROTATION_OFFSET = 30.0f;
const float BODY_RADIUS = 6.0f;
const float ARM_WIDTH = 32.0f;
const float ARM_HEIGHT = 2.0f;

BulbRenderer::BulbRenderer(const Bulb& bulb, ResourceManager& resourceManager)
    : m_bulb(bulb), m_resourceManager(resourceManager) {

    m_hexagonBg.setRadius(HEX_BG_RADIUS);
    m_hexagonBg.setPointCount(NUM_DIRECTIONS);
    m_hexagonBg.setOrigin(sf::Vector2f(HEX_BG_RADIUS, HEX_BG_RADIUS));
    m_hexagonBg.setFillColor(sf::Color::Transparent);
    m_hexagonBg.setOutlineThickness(HEX_BG_OUTLINE);
    m_hexagonBg.setRotation(sf::degrees(HEX_ROTATION_OFFSET));

    m_body.setRadius(BODY_RADIUS);
    m_body.setOrigin(sf::Vector2f(BODY_RADIUS, BODY_RADIUS));
    m_body.setOutlineThickness(HEX_BG_OUTLINE);
    m_body.setOutlineColor(sf::Color(150, 150, 150));

    m_armShape.setSize(sf::Vector2f(ARM_WIDTH, ARM_HEIGHT));
    m_armShape.setOrigin(sf::Vector2f(0.0f, ARM_HEIGHT / 2.0f));
}

void BulbRenderer::update() {
    float degrees = static_cast<float>(m_bulb.getOrientation()) * DIRECTION_ANGLE_STEP;
    this->setRotation(sf::degrees(degrees));

    if (m_bulb.isLit()) {
        m_hexagonBg.setOutlineColor(sf::Color(100, 100, 100, 50));
        m_body.setFillColor(sf::Color(255, 215, 0));
        m_body.setOutlineColor(sf::Color::Yellow);
        m_armShape.setFillColor(sf::Color(120, 140, 255));
    }
    else {
        m_hexagonBg.setOutlineColor(sf::Color(80, 80, 80, 40));
        m_body.setFillColor(sf::Color(100, 100, 100));
        m_body.setOutlineColor(sf::Color(130, 130, 130));
        m_armShape.setFillColor(sf::Color(70, 75, 90));
    }
}

void BulbRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_hexagonBg, states);

    for (int i = 0; i < NUM_DIRECTIONS; ++i)
    {
        Direction currentDir = static_cast<Direction>(i);
        if (m_bulb.hasArm(currentDir))
        {
            sf::RenderStates armStates = states;
            float armAngle = DirectionUtils::toAngle(currentDir);
            float orientationAngle = static_cast<float>(m_bulb.getOrientation()) * DIRECTION_ANGLE_STEP;
            armStates.transform.rotate(sf::degrees(armAngle - orientationAngle));
            target.draw(m_armShape, armStates);
        }
    }

    target.draw(m_body, states);
}