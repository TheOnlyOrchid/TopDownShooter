#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "assetpaths.h"
#include <vector>

// structs

struct Player
{
    float moveSpeed = 500.0f;
    sf::CircleShape sprite = sf::CircleShape(50.f);
};

struct Bullet
{
    float moveSpeed = 1000.0f;
    sf::CircleShape sprite = sf::CircleShape(5.f);
};

/*
    functions
*/

// utility

std::string getAssetPath(const std::string& relativePath)
{
    std::filesystem::path exePath = std::filesystem::current_path();
    return(exePath / relativePath).string();
}

// circle shape is TEMP, will be moved to player class later.
//player

bool keepPlayerInsideOfBounds(sf::CircleShape& player, const sf::Vector2u& windowSize)
{
    sf::Vector2f position = player.getPosition();

    // clamp x
    if (position.x < 0.f) {
        position.x = 0.f;
    }
    else if (position.x + player.getRadius() * 2 > windowSize.x) {
        position.x = windowSize.x - player.getRadius() * 2;
    }

    // clamp y
    if (position.y < 0.f) {
        position.y = 0.f;
    }
    else if (position.y + player.getRadius() * 2 > windowSize.y) {
        position.y = windowSize.y - player.getRadius() * 2;
    }

    player.setPosition(position);
    return true;
}

// combat

bool fireDefaultBullet(std::vector<Bullet>& bullets, Player& player)
{
    // if(cooldown) return
    Bullet bullet;

    bullet.sprite.setFillColor(sf::Color::Red);
    bullet.sprite.setPosition(
        sf::Vector2f(player.sprite.getPosition().x + player.sprite.getRadius() - bullet.sprite.getRadius(), player.sprite.getPosition().y)
    );
    bullets.push_back(bullet);
    
    return true;
}

bool cleanupBullets(std::vector<Bullet>& bullets)   {
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [&](const Bullet& b) { return b.sprite.getPosition().y < 0; }),
        bullets.end()
    );
    return true;
}

int main()
{   
    // assets
    sf::Font defaultFont;
    if (!defaultFont.openFromFile(getAssetPath(arialFontPath))) {
        std::cerr << "failed to load font arial" << std::endl;
    }

    /*
        game objects
    */

    // player
    Player player;

    // bullets
    std::vector<Bullet> bullets;

    /*
        Utility / misc
    */

    // timing

    // declare and initialisze delta clock 
    // TODO: may move into a "timing" class.
    sf::Clock deltaClock;
    deltaClock.start();

    // window
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "TopDownShooter");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            // close window.
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }   
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())    {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        } 
        // delta timer
        float deltaTime = deltaClock.restart().asSeconds();

        // TODO: extrapolate later 
        // input handling

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
            player.sprite.move(sf::Vector2f(0.0f, (-player.moveSpeed * deltaTime)));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
            player.sprite.move(sf::Vector2f(-player.moveSpeed * deltaTime, 0.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
            player.sprite.move(sf::Vector2f(player.moveSpeed * deltaTime, 0.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
            player.sprite.move(sf::Vector2f(0.0f, player.moveSpeed * deltaTime));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (fireDefaultBullet(bullets, player))
				window.draw(Bullet().sprite); // only draw bullet if it was fired.
            else {}
				// gun jam
        }

        cleanupBullets(bullets);
		keepPlayerInsideOfBounds(player.sprite, window.getSize());

        sf::Text text(defaultFont, "TopDownShooter", 25);

        window.clear();
		
        //draw here
        window.draw(text);

        window.draw(player.sprite);

        // draw all bullets
        for (auto& bullet : bullets)
            window.draw(bullet.sprite);
       
        window.display();
    }
}
