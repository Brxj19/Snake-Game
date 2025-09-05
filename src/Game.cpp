#include "Game.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics/CircleShape.hpp>

// #include<SFML/System/Clock.hpp>
// #include<SFML/System/Time.hpp>

Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode({640,384 }), "Snake Game", sf::Style::Close); //640 384
    // TODO:
    // Add first state to m_states
    m_context->m_state->Add(std::make_unique<MainMenu>(m_context), true);
}
Game::~Game() {}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    // sf::Clock clock;
    // sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        // timeSinceLastFrame += clock.restart();
        // while (timeSinceLastFrame > TIME_PER_FRAME)
        // {
            // timeSinceLastFrame -= TIME_PER_FRAME;
            m_context->m_state->ProcessStateChanges();
            m_context->m_state->getCurrent()->ProcessInput();
            m_context->m_state->getCurrent()->Update(TIME_PER_FRAME);
            m_context->m_state->getCurrent()->Draw();
        // }
    }
}