#include "BulbRenderer.h"
#include <cmath>

BulbRenderer::BulbRenderer(const Bulb& bulb, ResourceManager& resourceManager)
    : m_bulb(bulb), m_resourceManager(resourceManager) {

    m_hexagonBg.setRadius(38.0f);
    m_hexagonBg.setPointCount(6);
    m_hexagonBg.setOrigin(sf::Vector2f(38.0f, 38.0f));
    m_hexagonBg.setFillColor(sf::Color::Transparent);
    m_hexagonBg.setOutlineThickness(1.0f);
    m_hexagonBg.setRotation(sf::degrees(30.0f));

    m_body.setRadius(6.0f);
    m_body.setOrigin(sf::Vector2f(6.0f, 6.0f));
    m_body.setOutlineThickness(1.0f);
    m_body.setOutlineColor(sf::Color(150, 150, 150));

    m_armShape.setSize(sf::Vector2f(32.0f, 2.0f));
    m_armShape.setOrigin(sf::Vector2f(0.0f, 1.0f));
}

void BulbRenderer::update() {
    float degrees = static_cast<float>(m_bulb.getOrientation()) * 60.0f;
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
    states.transform *= getTransform(); // position + rotation orientation*60°

    target.draw(m_hexagonBg, states);

    for (int i = 0; i < 6; ++i)
    {
        Direction currentDir = static_cast<Direction>(i);
        if (m_bulb.hasArm(currentDir))
        {
            sf::RenderStates armStates = states;
            float armAngle = DirectionUtils::toAngle(currentDir);
            float orientationAngle = static_cast<float>(m_bulb.getOrientation()) * 60.0f;
            armStates.transform.rotate(sf::degrees(armAngle - orientationAngle));
            target.draw(m_armShape, armStates);
        }
    }

    target.draw(m_body, states);
}