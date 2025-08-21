#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class BulletUtils {
public:
    static void moveTowardsMouse(sf::Vector2f& position, float speed, float deltaTime,
        const sf::RenderWindow& window);

    static sf::Vector2f getDirectionToMouse(const sf::Vector2f& position,
        const sf::RenderWindow& window);
};