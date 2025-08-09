#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class AssetManager {
public:
    static AssetManager& getInstance();

    bool loadFont(const std::string& name, const std::string& path);
    const sf::Font& getFont(const std::string& name) const;

private:
    AssetManager() = default;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
};