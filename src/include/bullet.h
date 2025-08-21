#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "enemy.h"
#include "bulletcomponent.h"

class Bullet {
public:
    Bullet(const sf::Vector2f& position, float radius, sf::Color color, int pierce = 1);
    virtual ~Bullet();

    void update(float deltaTime, const sf::Vector2f& playerPosition,
        std::vector<std::unique_ptr<Enemy>>& enemies);
    void draw(sf::RenderWindow& window) const;
    bool isOutOfBounds(const sf::Vector2u& windowSize) const;
    bool shouldBeDestroyed() const { return pierce <= 0; }
    void onHitEnemy();

    const sf::CircleShape& getSprite() const { return sprite; }

protected:
    sf::CircleShape sprite;
    std::unique_ptr<BulletComponent> movementComponent;
    int pierce;
};

class DefaultBullet : public Bullet {
public:
    DefaultBullet(const sf::Vector2f& position, const sf::RenderWindow& window);
};

class HomingBullet : public Bullet {
public:
    HomingBullet(const sf::Vector2f& position, const sf::RenderWindow& window);
};

class LinearBullet : public Bullet {
public:
    LinearBullet(const sf::Vector2f& position, const sf::RenderWindow& window);
};