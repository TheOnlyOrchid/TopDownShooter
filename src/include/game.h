#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "player.h"
#include "bullet.h"
#include "enemy.h"

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
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    sf::Clock enemySpawnClock;
};