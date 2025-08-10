#include "Enemy.h"
#include "Config.h"
#include <SFML/Graphics/CircleShape.hpp>

// base enemy implementation
Enemy::Enemy(int x, int y, int health, float speed, sf::Color color)
    : x(x), y(y), health(health), speed(speed){
    sprite.setRadius(Config::ENEMY_RADIUS);
    sprite.setFillColor(color);
    sprite.setPosition(sf::Vector2f(x, y));
}

void Enemy::update(float deltaTime, const sf::Vector2f& playerPosition) {
    // move toward player
    sf::Vector2f direction = playerPosition - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }

    sprite.move(direction * speed * deltaTime);
    x = sprite.getPosition().x;
    y = sprite.getPosition().y;
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

bool Enemy::isAlive() const {
    return health > 0;
}

const sf::CircleShape& Enemy::getSprite() const {
    return sprite;
}

// defaultenemy
DefaultEnemy::DefaultEnemy(int x, int y)
    : Enemy(x, y, 100, Config::DEFAULT_ENEMY_SPEED, sf::Color(128, 0, 128)) { // purple
}