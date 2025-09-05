#pragma once

#include"State.hpp"
#include"Game.hpp"
#include"Snake.hpp"

#include<memory>

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Text.hpp>

class GamePlay : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        std::unique_ptr<sf::Sprite> m_grass;
        std::unique_ptr<sf::Sprite> m_food;
        std::array< std::unique_ptr<sf::Sprite> , 4 > m_walls;
        Snake m_snake;

        sf::Vector2f m_snakeDirection;
        sf::Time m_elapsedTime;

        std::unique_ptr<sf::Text> m_scoreText;
        int m_score;

        bool m_isPaused;
    public:
        GamePlay(std::shared_ptr<Context> &context);
        ~GamePlay();


        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void Pause()override;
        void Start()override;
};