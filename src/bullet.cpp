#include "Bullet.h"
#include "Config.h"

Bullet::Bullet(const sf::Vector2f& position) : moveSpeed(Config::BULLET_MOVE_SPEED) {
    sprite.setRadius(Config::BULLET_RADIUS);
    sprite.setFillColor(Config::BULLET_COLOR);
    sprite.setPosition(position);
}

void Bullet::update(float deltaTime) {
    sprite.move(sf::Vector2f(0.f, -moveSpeed * deltaTime));
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isOutOfBounds(const sf::Vector2u& windowSize) const {
    return sprite.getPosition().y < 0;
}