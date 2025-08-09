#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace Utils {
    std::string getAssetPath(const std::string& relativePath);
    bool keepShapeInsideBounds(sf::Shape& shape, const sf::Vector2u& bounds);
}