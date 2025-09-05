#pragma once

#include<memory>

#include"State.hpp"
#include"Game.hpp"

#include<SFML/Graphics/Text.hpp>

class PauseGame : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        std::unique_ptr<sf::Text> m_pauseTitle;
    public:
        PauseGame(std::shared_ptr<Context> &context);
        ~PauseGame();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};
