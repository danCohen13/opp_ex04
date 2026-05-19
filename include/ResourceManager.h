#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    // Standard copy and assignment protection for resource safety
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Acquires a reference to a sf::Texture, loading it if not already cached
    const sf::Texture& getTexture(const std::string& filepath);

    // Acquires a reference to a sf::Font, loading it if not already cached
    const sf::Font& getFont(const std::string& filepath);

    // Clears all resource maps from memory
    void clear();

private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
};