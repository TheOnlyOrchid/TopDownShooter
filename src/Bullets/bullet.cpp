#include "Bullet.h"
#include "BulletComponent.h"
#include "Config.h"
#include "Enemy.h"
#include <SFML/Graphics/CircleShape.hpp>

// base bullet implementation
Bullet::Bullet(const sf::Vector2f& position, float radius, sf::Color color, int pierce)
    : pierce(pierce) {
    sprite.setRadius(radius);
    sprite.setFillColor(color);
    sprite.setPosition(position);
}

Bullet::~Bullet() = default;

void Bullet::update(float deltaTime, const sf::Vector2f& playerPosition,
    std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (movementComponent) {
        sf::Vector2f position = sprite.getPosition();
        movementComponent->update(deltaTime, position, playerPosition, enemies);
        sprite.setPosition(position);
    }

    // Check for collisions with enemies
    sf::FloatRect bulletBounds = sprite.getGlobalBounds();
    for (auto& enemy : enemies) {
        if (enemy->isAlive()) {
            auto intersection = bulletBounds.findIntersection(enemy->getSprite().getGlobalBounds());
            if (intersection) {
                enemy->takeDamage(10); // TODO: make damage configurable in bullet implentations, and at runtime, possibly make it rely on stats.
                onHitEnemy();
                if(pierce <= 0) break; // break when pierce = 0
            }
        }
    }
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isOutOfBounds(const sf::Vector2u& windowSize) const {
    sf::Vector2f pos = sprite.getPosition();
    float radius = sprite.getRadius();

    return pos.x + radius < 0 ||
        pos.x - radius > windowSize.x ||
        pos.y + radius < 0 ||
        pos.y - radius > windowSize.y;
}

void Bullet::onHitEnemy() {
    pierce--;
}

// defaultBullet (homing)
DefaultBullet::DefaultBullet(const sf::Vector2f& position, const sf::RenderWindow& window)
    : Bullet(position, Config::BULLET_RADIUS, Config::BULLET_COLOR, 1) {
    movementComponent = std::make_unique<HomingComponent>(Config::BULLET_MOVE_SPEED, window);
}

// HomingBullet (explicitly homing)
HomingBullet::HomingBullet(const sf::Vector2f& position, const sf::RenderWindow& window)
    : Bullet(position, Config::BULLET_RADIUS, Config::BULLET_COLOR, 1) {
    movementComponent = std::make_unique<HomingComponent>(Config::BULLET_MOVE_SPEED, window);
}

// LinearBullet (aims then goes straight)
LinearBullet::LinearBullet(const sf::Vector2f& position, const sf::RenderWindow& window)
    : Bullet(position, Config::BULLET_RADIUS, sf::Color::Blue, 2) {
    movementComponent = std::make_unique<LinearComponent>(Config::BULLET_MOVE_SPEED, window);
}