#pragma once

#include <SFML/Graphics.hpp>
#include "Bulb.h"
#include "ResourceManager.h"
#include "Direction.h"

class BulbRenderer : public sf::Drawable, public sf::Transformable {
public:
    BulbRenderer(const Bulb& bulb, ResourceManager& resourceManager);
    void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    const Bulb& m_bulb;
    ResourceManager& m_resourceManager;

    sf::CircleShape m_hexagonBg;
    sf::CircleShape m_body;
    sf::RectangleShape m_armShape;

};