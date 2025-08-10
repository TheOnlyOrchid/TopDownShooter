#include "Bullet.h"
#include "Config.h"

// base bullet implementation
Bullet::Bullet(const sf::Vector2f& position, float speed, float radius, sf::Color color)
    : speed(speed) {
    sprite.setRadius(radius);
    sprite.setFillColor(color);
    sprite.setPosition(position);
}

void Bullet::update(float deltaTime) {
    sprite.move(sf::Vector2f(0.f, -speed * deltaTime)); // js moves upwards for now
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isOutOfBounds(const sf::Vector2u& windowSize) const {
    return sprite.getPosition().y < 0 ||
        sprite.getPosition().y > windowSize.y ||
        sprite.getPosition().x < 0 ||
        sprite.getPosition().x > windowSize.x;
}

DefaultBullet::DefaultBullet(const sf::Vector2f& position)
    : Bullet(position, Config::BULLET_MOVE_SPEED, Config::BULLET_RADIUS, Config::BULLET_COLOR) {
}