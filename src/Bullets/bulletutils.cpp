#include "BulletUtils.h"
#include <SFML/Window/Mouse.hpp>
#include <cmath>

void BulletUtils::moveTowardsMouse(sf::Vector2f& position, float speed, float deltaTime,
    const sf::RenderWindow& window) {
    sf::Vector2f direction = getDirectionToMouse(position, window);
    position += direction * speed * deltaTime;
}

sf::Vector2f BulletUtils::getDirectionToMouse(const sf::Vector2f& position,
    const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    sf::Vector2f direction = worldMousePos - position;
    float length = std::hypot(direction.x, direction.y);

    if (length != 0) {
        direction /= length;
    }

    return direction;
}