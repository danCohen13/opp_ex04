#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    const sf::Texture& getTexture(const std::string& filepath);

    const sf::Font& getFont(const std::string& filepath);

    void clear();

private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
};