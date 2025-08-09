#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Bullet.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    Player player;
    std::vector<Bullet> bullets;
};