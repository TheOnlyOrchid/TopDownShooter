#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "assetpaths.h"

std::string getAssetPath(const std::string& relativePath)
{
    std::filesystem::path exePath = std::filesystem::current_path();
    return(exePath / relativePath).string();
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
                if (keyPressed->scancode == sf::Keyboard::Scan::W)
                    playerSprite.move(sf::Vector2f(0.0f, -5.0f));

                if (keyPressed->scancode == sf::Keyboard::Scan::A)
                    playerSprite.move(sf::Vector2f(-5.0f, 0.0f));
               
                if (keyPressed->scancode == sf::Keyboard::Scan::D)
                    playerSprite.move(sf::Vector2f(5.0f, 0.0f));

                if (keyPressed->scancode == sf::Keyboard::Scan::S)
                    playerSprite.move(sf::Vector2f(0.0f, 5.0f));
            }
        } 

        sf::Text text(defaultFont, "TopDownShooter", 25);

        window.clear();
		
        //draw here
        window.draw(text);

        window.draw(playerSprite);
        
        //finalise
        window.display();
    }
}
