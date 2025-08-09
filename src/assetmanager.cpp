#include "AssetManager.h"
#include "Utils.h"

AssetManager& AssetManager::getInstance() {
    static AssetManager instance;
    return instance;
}

bool AssetManager::loadFont(const std::string& name, const std::string& path) {
    auto font = std::make_unique<sf::Font>();
    if (!font->openFromFile(Utils::getAssetPath(path))) {
        return false;
    }
    fonts[name] = std::move(font);
    return true;
}

const sf::Font& AssetManager::getFont(const std::string& name) const {
    return *fonts.at(name);
}