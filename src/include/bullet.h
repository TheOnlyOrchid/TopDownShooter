#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Bullet {
protected:
    sf::CircleShape sprite;
    float speed;

public:
    Bullet(const sf::Vector2f& position, float speed, float radius, sf::Color color);
    virtual ~Bullet() = default;

    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window) const;
    virtual bool isOutOfBounds(const sf::Vector2u& windowSize) const;
};

class DefaultBullet : public Bullet {
public:
    DefaultBullet(const sf::Vector2f& position);
};