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
    sf::Font defaultFont;
    if (!defaultFont.openFromFile(getAssetPath(arialFontPath))) {
        std::cerr << "failed to load font from" << std::endl;
    }

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "TopDownShooter");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        sf::Text text(defaultFont, "TopDownShooter", 25);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        

        window.clear();
		
        //draw here
        window.draw(text);
        
        //finalise
        window.display();
    }
}
