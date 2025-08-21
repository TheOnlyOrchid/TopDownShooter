#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "BulletComponent.h"
#include "Enemy.h"
#include <limits>
#include <cmath>
#include "BulletUtils.h"

// homing component
HomingComponent::HomingComponent(float speed, const sf::RenderWindow& window)
    : speed(speed), window(window) {
}

void HomingComponent::update(float deltaTime, sf::Vector2f& position, const sf::Vector2f& playerPosition,
    const std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (enemies.empty()) {
        BulletUtils::moveTowardsMouse(position, speed, deltaTime, window);
        return;
    }

    sf::Vector2f closestEnemyPos;
    float smallestDistance = std::numeric_limits<float>::max();

    // find closest enemy to player
    for (const auto& enemy : enemies) {
        sf::Vector2f enemyDistance = playerPosition - enemy->getSprite().getPosition();
        float distSq = (enemyDistance.x * enemyDistance.x) + (enemyDistance.y * enemyDistance.y);

        if (smallestDistance >= distSq) {
            smallestDistance = distSq;
            closestEnemyPos = enemy->getSprite().getPosition();
        }
    }

    // move towards closest enemy
    sf::Vector2f distance = closestEnemyPos - position;
    float length = std::hypot(distance.x, distance.y);

    if (length != 0) {
        distance /= length;
        position += distance * speed * deltaTime;
    }
}

// linear component
LinearComponent::LinearComponent(float speed, const sf::RenderWindow& window)
    : speed(speed), hasDirection(false), window(window) {
}

void LinearComponent::update(float deltaTime, sf::Vector2f& position, const sf::Vector2f& playerPosition,
    const std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (!hasDirection) {
        // set initial direction
        if (!enemies.empty()) {
            sf::Vector2f closestEnemyPos;
            float smallestDistance = std::numeric_limits<float>::max();

            for (const auto& enemy : enemies) {
                sf::Vector2f enemyDistance = playerPosition - enemy->getSprite().getPosition();
                float distSq = (enemyDistance.x * enemyDistance.x) + (enemyDistance.y * enemyDistance.y);

                if (smallestDistance >= distSq) {
                    smallestDistance = distSq;
                    closestEnemyPos = enemy->getSprite().getPosition();
                }
            }

            direction = closestEnemyPos - position;
            float length = std::hypot(direction.x, direction.y);
            if (length != 0) {
                direction /= length;
            }
        }
        else {
            BulletUtils::moveTowardsMouse(position, speed, deltaTime, window);
        }
        hasDirection = true;
    }

    // just continue moving 
    position += direction * speed * deltaTime;
}