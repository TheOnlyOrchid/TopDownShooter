#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Enemy {
protected:
    int x, y;
    int health;
    float speed;
    sf::CircleShape sprite;

public:
    Enemy(int x, int y, int health, float speed, sf::Color color);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime, const sf::Vector2f& playerPosition);
    virtual void draw(sf::RenderWindow& window) const;
    virtual void takeDamage(int damage);
    virtual bool isAlive() const;
    const sf::CircleShape& getSprite() const;
};

class DefaultEnemy : public Enemy {
public:
    DefaultEnemy(int x, int y);
};