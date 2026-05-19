#include "ResourceManager.h"
#include "Exceptions.h"

const sf::Texture& ResourceManager::getTexture(const std::string& filepath) {
    auto it = m_textures.find(filepath);
    if (it != m_textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) {
        throw GameException("Graphics Error: Failed to load texture file: " + filepath);
    }

    auto inserted = m_textures.insert({ filepath, texture });
    return inserted.first->second;
}

const sf::Font& ResourceManager::getFont(const std::string& filepath) {
    auto it = m_fonts.find(filepath);
    if (it != m_fonts.end()) {
        return it->second;
    }

    sf::Font font;
    // CORRECTION SFML 3 : loadFromFile est devenu openFromFile pour les polices
    if (!font.openFromFile(filepath)) {
        throw GameException("Graphics Error: Failed to load font file: " + filepath);
    }

    auto inserted = m_fonts.insert({ filepath, font });
    return inserted.first->second;
}

void ResourceManager::clear() {
    m_textures.clear();
    m_fonts.clear();
}