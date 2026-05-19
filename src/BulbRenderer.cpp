#include "BulbRenderer.h"
#include <cmath>

BulbRenderer::BulbRenderer(const Bulb& bulb, ResourceManager& resourceManager)
    : m_bulb(bulb), m_resourceManager(resourceManager) {

    // 1. FOND HEXAGONAL POINTU VERS LE HAUT
    m_hexagonBg.setRadius(38.0f);
    m_hexagonBg.setPointCount(6);
    m_hexagonBg.setOrigin(sf::Vector2f(38.0f, 38.0f));
    m_hexagonBg.setFillColor(sf::Color::Transparent); // Transparent comme le modèle
    m_hexagonBg.setOutlineThickness(1.0f);
    // Rotation de 30 degrés pour redresser l'hexagone "pointu vers le haut"
    m_hexagonBg.setRotation(sf::degrees(30.0f));

    // 2. PETITE SPHÈRE CENTRALE (Plus discrète, comme l'image de droite)
    m_body.setRadius(6.0f);
    m_body.setOrigin(sf::Vector2f(6.0f, 6.0f));
    m_body.setOutlineThickness(1.0f);
    m_body.setOutlineColor(sf::Color(150, 150, 150));

    // 3. TIGE FINE (Un bras conducteur discret qui part du centre vers le bord)
    m_armShape.setSize(sf::Vector2f(32.0f, 2.0f)); // Plus fin et plus long
    m_armShape.setOrigin(sf::Vector2f(0.0f, 1.0f));
}

void BulbRenderer::update() {
    // Rotation globale de l'ampoule (60 degrés par cran)
    float degrees = static_cast<float>(m_bulb.getOrientation()) * 60.0f;
    this->setRotation(sf::degrees(degrees));

    // Application des couleurs du modèle de droite
    if (m_bulb.isLit()) {
        m_hexagonBg.setOutlineColor(sf::Color(100, 100, 100, 50)); // Contour très discret
        m_body.setFillColor(sf::Color(255, 215, 0));              // Or / Jaune brillant
        m_body.setOutlineColor(sf::Color::Yellow);
        m_armShape.setFillColor(sf::Color(120, 140, 255));        // Bleu-gris lumineux pour le courant
    }
    else {
        m_hexagonBg.setOutlineColor(sf::Color(80, 80, 80, 40));
        m_body.setFillColor(sf::Color(100, 100, 100));            // Gris métal éteint
        m_body.setOutlineColor(sf::Color(130, 130, 130));
        m_armShape.setFillColor(sf::Color(70, 75, 90));            // Métal sombre inactif
    }
}

void BulbRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    // Dessin du fond hexagonal
    target.draw(m_hexagonBg, states);

    // Dessin des bras conducteurs
    for (int i = 0; i < 6; ++i)
    {
        Direction currentDir = static_cast<Direction>(i);

        if (m_bulb.hasArm(currentDir))
        {
            sf::RenderStates armStates = states;

            // Conversion logique -> angle graphique
            float armAngle = DirectionUtils::toAngle(currentDir);

            // Rotation du bras autour du centre
            armStates.transform.rotate(sf::degrees(armAngle));

            // Dessin du bras
            target.draw(m_armShape, armStates);
        }
    }

    // Dessin du noyau central par-dessus les bras
    target.draw(m_body, states);
}