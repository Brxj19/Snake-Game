#include "MainMenu.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : m_context(context), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false),
      m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{
}

MainMenu::~MainMenu() {}

void MainMenu::Init()
{
    m_context->m_asset->AddFont(MAIN_FONT, "./assets/font/DynaPuff-Regular.ttf");

    sf::Vector2u windowSize = m_context->m_window->getSize();

    m_gameTitle = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Snake Game",30);
    m_gameTitle->setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_gameTitle->getLocalBounds();
    m_gameTitle->setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,bounds.position.y + bounds.size.y / 2.0f));
    m_gameTitle->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 150));
    
    //play button
    m_playButton = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Play",30);
    m_playButton->setFillColor(sf::Color::White);
    sf::FloatRect play_bounds = m_playButton->getLocalBounds();
    m_playButton->setOrigin(sf::Vector2f(play_bounds.position.x + play_bounds.size.x / 2.0f, play_bounds.position.y + play_bounds.size.y / 2.0f));
    m_playButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 30));
    
    //exit button
    m_exitButton = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Exit",30);
    m_exitButton->setFillColor(sf::Color::White);
    sf::FloatRect exit_bounds = m_exitButton->getLocalBounds();
    m_exitButton->setOrigin(sf::Vector2f(exit_bounds.position.x + exit_bounds.size.x / 2.0f,exit_bounds.position.y + exit_bounds.size.y / 2.0f));
    m_exitButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 + 30));


}

void MainMenu::ProcessInput()
{
    while (auto event = m_context->m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>()){
            m_context->m_window->close();
        }
        else if( event->is<sf::Event::KeyPressed>() ){
            if(const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            switch (static_cast<sf::Keyboard::Key>(keyEvent->code))
            {
                case sf::Keyboard::Key::Up:
                {
                    if(!m_isPlayButtonSelected){
                        m_isPlayButtonSelected = true;
                        m_isExitButtonSelected = false;
                        // m_playButton->setFillColor(sf::Color::Red);
                        // m_exitButton->setFillColor(sf::Color::White);
                    }
                    break;
                }
                case sf::Keyboard::Key::Down:
                {
                    if(!m_isExitButtonSelected){
                        m_isPlayButtonSelected = false;
                        m_isExitButtonSelected = true;
                        // m_playButton->setFillColor(sf::Color::White);
                        // m_exitButton->setFillColor(sf::Color::Red);
                    }
                    break;
                }
                case sf::Keyboard::Key::W:
                {
                    if(!m_isPlayButtonSelected){
                        m_isPlayButtonSelected = true;
                        m_isExitButtonSelected = false;
                        // m_playButton->setFillColor(sf::Color::Red);
                        // m_exitButton->setFillColor(sf::Color::White);
                    }
                    break;
                }
                case sf::Keyboard::Key::S:
                {
                    if(!m_isExitButtonSelected){
                        m_isPlayButtonSelected = false;
                        m_isExitButtonSelected = true;
                        // m_playButton->setFillColor(sf::Color::White);
                        // m_exitButton->setFillColor(sf::Color::Red);
                    }
                    break;
                }
                case sf::Keyboard::Key::Enter:
                {
                    m_isExitButtonPressed = false;
                    m_isPlayButtonPressed = false;

                    if(m_isPlayButtonSelected){
                        m_isPlayButtonPressed = true;
                    }
                    else{
                        m_isExitButtonPressed = true;
                    }
                    break;
                }
                default:
                    break;
            }
        }
            
    }
}

void MainMenu::Update([[maybe_unused]] sf::Time deltaTime) {
    if(m_isPlayButtonSelected){
        m_playButton->setFillColor(sf::Color(176,236,172));
        m_exitButton->setFillColor(sf::Color::White);
    }
    else{
        m_exitButton->setFillColor(sf::Color(176,236,172));
        m_playButton->setFillColor(sf::Color::White);
    }

    if(m_isPlayButtonPressed){
        m_context->m_state->Add(std::make_unique<GamePlay>(m_context), true);
        // m_isPlayButtonPressed = false;
    }
    else if(m_isExitButtonPressed){
        m_context->m_window->close();
    }
}

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color(0,158,164));
    m_context->m_window->draw(*(m_gameTitle));
    m_context->m_window->draw(*(m_playButton));
    m_context->m_window->draw(*(m_exitButton));
    m_context->m_window->display();
}
