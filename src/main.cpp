#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "assetpaths.h"

std::string getAssetPath(const std::string& relativePath)
{
    std::filesystem::path exePath = std::filesystem::current_path();
    return(exePath / relativePath).string();
}

// circle shape is TEMP, will be moved to player class later.
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

struct Player 
{
    const float moveSpeed = 500.0f;
	sf::CircleShape sprite = sf::CircleShape(50.f);
};

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

        // TODO: extrapolate later 
        // input handling

		float deltaTime = deltaClock.getElapsedTime().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
            player.sprite.move(sf::Vector2f(0.0f, (-player.moveSpeed * deltaTime)));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
            player.sprite.move(sf::Vector2f(-player.moveSpeed * deltaTime, 0.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
            player.sprite.move(sf::Vector2f(player.moveSpeed * deltaTime, 0.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
            player.sprite.move(sf::Vector2f(0.0f, player.moveSpeed * deltaTime));

		keepPlayerInsideOfBounds(player.sprite, window.getSize());

        sf::Text text(defaultFont, "TopDownShooter", 25);

        window.clear();
		
        //draw here
        window.draw(text);

        window.draw(player.sprite);
        
        //finalise
        deltaClock.restart(); // restart delta clock each frame.
        window.display();
    }
}
