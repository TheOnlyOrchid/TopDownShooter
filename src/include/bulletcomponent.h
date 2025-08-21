#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>
#include "Enemy.h"

class BulletComponent {
public:
    virtual void update(float deltaTime, sf::Vector2f& position, const sf::Vector2f& playerPosition,
        const std::vector<std::unique_ptr<Enemy>>& enemies) = 0;
    virtual ~BulletComponent() = default;
};

class HomingComponent : public BulletComponent {
public:
    HomingComponent(float speed, const sf::RenderWindow& window);
    void update(float deltaTime, sf::Vector2f& position, const sf::Vector2f& playerPosition,
        const std::vector<std::unique_ptr<Enemy>>& enemies) override;

private:
    float speed;
    const sf::RenderWindow& window;
};

class LinearComponent : public BulletComponent {
public:
    LinearComponent(float speed, const sf::RenderWindow& window);
    void update(float deltaTime, sf::Vector2f& position, const sf::Vector2f& playerPosition,
        const std::vector<std::unique_ptr<Enemy>>& enemies) override;

private:
    float speed;
    bool hasDirection;
    sf::Vector2f direction;
    const sf::RenderWindow& window;
};