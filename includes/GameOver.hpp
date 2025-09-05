#pragma once

#include<memory>

#include"State.hpp"
#include"Game.hpp"

#include<SFML/Graphics/Text.hpp>

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    std::unique_ptr<sf::Text> m_gameOverTitle;
    std::unique_ptr<sf::Text> m_retryButton;
    std::unique_ptr<sf::Text> m_exitButton;

    bool m_isRetryButtonSelected;
    bool m_isRetryButtonPressed;
    
    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    GameOver(std::shared_ptr<Context> &context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
