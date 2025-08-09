#include "Utils.h"

std::string Utils::getAssetPath(const std::string& relativePath) {
    std::filesystem::path exePath = std::filesystem::current_path();
    return (exePath / relativePath).string();
}

bool Utils::keepShapeInsideBounds(sf::Shape& shape, const sf::Vector2u& bounds) {
    sf::Vector2f position = shape.getPosition();
    sf::FloatRect boundsRect = shape.getGlobalBounds();

    // clamp x
    if (position.x < 0.f) {
        position.x = 0.f;
    }
    else if (position.x + boundsRect.size.x > bounds.x) {
        position.x = bounds.x - boundsRect.size.x;
    }

    // clamp y
    if (position.y < 0.f) {
        position.y = 0.f;
    }
    else if (position.y + boundsRect.size.y > bounds.y) {
        position.y = bounds.y - boundsRect.size.y;
    }

    shape.setPosition(position);
    return true;
}