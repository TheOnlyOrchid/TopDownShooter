#include "Game.h"
#include "Config.h"
#include "AssetManager.h"
#include "Utils.h"
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>

Game::Game() : window(sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }), "TopDownShooter") {
    window.setFramerateLimit(Config::FRAME_RATE_LIMIT);

    // Initialize assets here
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

    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }

    // erare bullets outside of the map
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [this](const Bullet& b) { return b.isOutOfBounds(window.getSize()); }),
        bullets.end());

    // fire
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f spawnPosition = player.getPosition();
        spawnPosition.x += Config::PLAYER_RADIUS - Config::BULLET_RADIUS;
        bullets.emplace_back(spawnPosition);
    }

    // keep player in bounds
    Utils::keepShapeInsideBounds(player.getSprite(), window.getSize());
}

void Game::render() {
    window.clear();

    // draw game objects (current order, player, bullets,)
    player.draw(window);
    for (const auto& bullet : bullets) {
        bullet.draw(window);
    }

    // draw UI (current order, text,)
    sf::Text text(AssetManager::getInstance().getFont("arial"), "TopDownShooter", Config::DEFAULT_FONT_SIZE);
    window.draw(text);

    window.display();
}