#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

class Player {
public:
    Player();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void handleInput(float deltaTime);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    const sf::CircleShape& Player::getSprite() const;
    sf::CircleShape& Player::getSprite();

private:
    sf::CircleShape sprite;
    float moveSpeed;
};