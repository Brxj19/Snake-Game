#pragma once

#include<list>
#include<memory>

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable{
    private:
        std::list< std::unique_ptr<sf::Sprite> > m_body;
        std::list< std::unique_ptr<sf::Sprite> >::iterator m_head;
        std::list< std::unique_ptr<sf::Sprite> >::iterator m_tail;
    public:
        Snake();
        ~Snake();

        void Init(const sf::Texture &texture);
        void Move(const sf::Vector2f &direction);
        bool IsOn(sf::Sprite &other) const;
        void Grow(const sf::Vector2f &direction);
        bool isSelfIntersecting() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        bool isFoodSnakeIntersecting(sf::Sprite &other)const;
        
};