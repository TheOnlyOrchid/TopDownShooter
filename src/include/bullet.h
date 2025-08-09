#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

class Bullet {
public:
    Bullet(const sf::Vector2f& position);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isOutOfBounds(const sf::Vector2u& windowSize) const;

private:
    sf::CircleShape sprite;
    float moveSpeed;
};