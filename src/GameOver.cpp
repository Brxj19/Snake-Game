#include"GameOver.hpp"
#include"GamePlay.hpp"

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context), m_isRetryButtonSelected(true), m_isRetryButtonPressed(false),
      m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{


    sf::Vector2u windowSize = m_context->m_window->getSize();

    m_gameOverTitle = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Game Over",30);
    m_gameOverTitle->setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_gameOverTitle->getLocalBounds();
    m_gameOverTitle->setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,bounds.position.y + bounds.size.y / 2.0f));
    m_gameOverTitle->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 150));
    
    //play button
    m_retryButton = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Retry",30);
    m_retryButton->setFillColor(sf::Color::White);
    sf::FloatRect play_bounds = m_retryButton->getLocalBounds();
    m_retryButton->setOrigin(sf::Vector2f(play_bounds.position.x + play_bounds.size.x / 2.0f, play_bounds.position.y + play_bounds.size.y / 2.0f));
    m_retryButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 30));
    
    //exit button
    m_exitButton = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Exit",30);
    m_exitButton->setFillColor(sf::Color::White);
    sf::FloatRect exit_bounds = m_exitButton->getLocalBounds();
    m_exitButton->setOrigin(sf::Vector2f(exit_bounds.position.x + exit_bounds.size.x / 2.0f,exit_bounds.position.y + exit_bounds.size.y / 2.0f));
    m_exitButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 + 30));


}

void GameOver::ProcessInput()
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
                    if(!m_isRetryButtonSelected){
                        m_isRetryButtonSelected = true;
                        m_isExitButtonSelected = false;
                        // m_playButton->setFillColor(sf::Color::Red);
                        // m_exitButton->setFillColor(sf::Color::White);
                    }
                    break;
                }
                case sf::Keyboard::Key::Down:
                {
                    if(!m_isExitButtonSelected){
                        m_isRetryButtonSelected = false;
                        m_isExitButtonSelected = true;
                        // m_playButton->setFillColor(sf::Color::White);
                        // m_exitButton->setFillColor(sf::Color::Red);
                    }
                    break;
                }
                case sf::Keyboard::Key::Enter:
                {
                    m_isExitButtonPressed = false;
                    m_isRetryButtonPressed = false;

                    if(m_isRetryButtonSelected){
                        m_isRetryButtonPressed = true;
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

void GameOver::Update([[maybe_unused]] sf::Time deltaTime) {
    if(m_isRetryButtonSelected){
        m_retryButton->setFillColor(sf::Color(176,236,172));
        m_exitButton->setFillColor(sf::Color::White);
    }
    else{
        m_exitButton->setFillColor(sf::Color(176,236,172));
        m_retryButton->setFillColor(sf::Color::White);
    }

    if(m_isRetryButtonPressed){
        m_context->m_state->Add(std::make_unique<GamePlay>(m_context), true);
        // m_isPlayButtonPressed = false;
    }
    else if(m_isExitButtonPressed){
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color(0,158,164));
    m_context->m_window->draw(*(m_gameOverTitle));
    m_context->m_window->draw(*(m_retryButton));
    m_context->m_window->draw(*(m_exitButton));
    m_context->m_window->display();
}
