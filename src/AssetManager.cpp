#include"AssetManager.hpp"

Engine::AssetManager::AssetManager(){}
Engine::AssetManager::~AssetManager(){}

void Engine::AssetManager::AddTexture(int id, const string &filePath, bool isRepeated){
    auto texture = std::make_unique<sf::Texture>();
    if(!texture->loadFromFile(filePath)){
        throw std::runtime_error("Failed to load font: " + filePath);
    }
    texture->setRepeated(isRepeated);
    m_textures[id] = std::move(texture);
}

void Engine::AssetManager::AddFont(int id, const string &filePath){
    // auto font = std::unique_ptr<sf::Font>();
    // if(font->openFromFile(filePath)){
    //     m_fonts[id] = std::move(font);
    // }
    auto font = std::make_unique<sf::Font>();
    if (!font->openFromFile(filePath)) {
        throw std::runtime_error("Failed to load font: " + filePath);
    }
    m_fonts[id] = std::move(font);
}

const sf::Texture& Engine::AssetManager::getTexture(int id) const{
    return *(m_textures.at(id).get());
}

const sf::Font& Engine::AssetManager::getFont(int id) const{
    return *(m_fonts.at(id).get());
}   