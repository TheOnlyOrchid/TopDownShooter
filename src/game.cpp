#include "Game.h"
#include "Config.h"
#include "AssetManager.h"
#include "Utils.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>

Game::Game() : window(sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }), "TopDownShooter") {
    window.setFramerateLimit(Config::FRAME_RATE_LIMIT);

    // initialize assets here
    AssetManager::getInstance().loadFont("arial", "assets/fonts/arial.ttf");
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
        }
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);

    // update bullets
    for (auto& bullet : bullets) {
        bullet->update(deltaTime);
    }

    // remove out-of-bounds bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [this](const std::unique_ptr<Bullet>& b) {
            return b->isOutOfBounds(window.getSize());
        }),
        bullets.end());

    // spawn enemies periodically
    if (enemySpawnClock.getElapsedTime().asSeconds() > Config::ENEMY_SPAWN_INTERVAL) {
        int x = rand() % Config::WINDOW_WIDTH;
        enemies.push_back(std::make_unique<DefaultEnemy>(x, -50));
        enemySpawnClock.restart();
    }

    // update enemies
    for (auto& enemy : enemies) {
        enemy->update(deltaTime, player.getPosition());
    }

    // remove dead enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const std::unique_ptr<Enemy>& e) {
            return !e->isAlive();
        }),
        enemies.end());

    // fire bullets
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f spawnPosition = player.getPosition();
        spawnPosition.x += Config::PLAYER_RADIUS - Config::BULLET_RADIUS;
        bullets.push_back(std::make_unique<DefaultBullet>(spawnPosition));
    }

    Utils::keepShapeInsideBounds(player.getSprite(), window.getSize());
}

void Game::render() {
    window.clear();

    // enemies
    for (const auto& enemy : enemies) {
        enemy->draw(window);
    }

    player.draw(window);

    // bullets
    for (const auto& bullet : bullets) {
        bullet->draw(window);
    }

    // UI
    sf::Text text(AssetManager::getInstance().getFont("arial"), "TopDownShooter", Config::DEFAULT_FONT_SIZE);
    window.draw(text);

    window.display();
}