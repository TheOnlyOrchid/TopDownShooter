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
    std::cout << "Player position: " << position.x << ", " << position.y << std::endl;

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

    //player
    sf::CircleShape playerSprite(50.f);

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

            // input handling
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
                    playerSprite.move(sf::Vector2f(0.0f, -5.0f));

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
                    playerSprite.move(sf::Vector2f(-5.0f, 0.0f));

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
                    playerSprite.move(sf::Vector2f(5.0f, 0.0f));

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
                    playerSprite.move(sf::Vector2f(0.0f, 5.0f));*/
            }
        } 

        // TODO: extrapolate later 
        // input handling
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
            playerSprite.move(sf::Vector2f(0.0f, -5.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
            playerSprite.move(sf::Vector2f(-5.0f, 0.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
            playerSprite.move(sf::Vector2f(5.0f, 0.0f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
            playerSprite.move(sf::Vector2f(0.0f, 5.0f));

		keepPlayerInsideOfBounds(playerSprite, window.getSize());

        sf::Text text(defaultFont, "TopDownShooter", 25);

        window.clear();
		
        //draw here
        window.draw(text);

        window.draw(playerSprite);
        
        //finalise
        window.display();
    }
}
