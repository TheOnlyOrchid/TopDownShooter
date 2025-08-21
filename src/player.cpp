#include "Player.h"
#include "Config.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() : moveSpeed(Config::PLAYER_MOVE_SPEED) {
    sprite.setRadius(Config::PLAYER_RADIUS);
    sprite.setFillColor(Config::PLAYER_COLOR);
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
        movement.y -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
        movement.y += moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
        movement.x -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
        movement.x += moveSpeed * deltaTime;

    sprite.move(movement);
}

void Player::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

// returns top left of sprite :(
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::CircleShape& Player::getSprite() {
    return sprite;
}
const sf::CircleShape& Player::getSprite() const {
    return sprite;
}