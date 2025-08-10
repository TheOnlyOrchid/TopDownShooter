#pragma once
#include <SFML/Graphics.hpp>

namespace Config {
    // player
    constexpr float PLAYER_MOVE_SPEED = 500.0f;
    constexpr float PLAYER_RADIUS = 50.0f;
    constexpr sf::Color PLAYER_COLOR = sf::Color::White;

    // bullet
    constexpr float BULLET_MOVE_SPEED = 1000.0f;
    constexpr float BULLET_RADIUS = 5.0f;
    constexpr sf::Color BULLET_COLOR = sf::Color::Red;

    // Enemy config
    constexpr float ENEMY_RADIUS = 20.f;
    constexpr float DEFAULT_ENEMY_SPEED = 200.f;
    constexpr float ENEMY_SPAWN_INTERVAL = 2.0f; // seconds

    // TODO: make this variable and dependant on in-game settings.
    constexpr unsigned int WINDOW_WIDTH = 1920;
    constexpr unsigned int WINDOW_HEIGHT = 1080;
    constexpr unsigned int FRAME_RATE_LIMIT = 144;

    // font
    constexpr unsigned int DEFAULT_FONT_SIZE = 25;
}