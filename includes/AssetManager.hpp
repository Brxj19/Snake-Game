#pragma once

#include<map>
#include<memory>
#include<string>

#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Font.hpp>

using namespace std;

namespace Engine{
    class AssetManager{
        private:
            map<int,unique_ptr<sf::Texture>> m_textures;
            map<int,unique_ptr<sf::Font>> m_fonts;
        public:
            AssetManager();
            ~AssetManager();

            void AddTexture(int id, const string &filePath, bool isRepeated = false);
            void AddFont(int id, const string &filePath);

            const sf::Texture& getTexture(int id) const;
            const sf::Font& getFont(int id) const;

    };
}