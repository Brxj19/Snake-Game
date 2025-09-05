#include"PauseGame.hpp"

PauseGame:: PauseGame(  std::shared_ptr<Context> &context): m_context(context){

}
PauseGame:: ~PauseGame(){

}

void PauseGame:: Init(){
    sf::Vector2u windowSize = m_context->m_window->getSize();

    m_pauseTitle = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Paused",30);
    m_pauseTitle->setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_pauseTitle->getLocalBounds();
    m_pauseTitle->setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,bounds.position.y + bounds.size.y / 2.0f));
    m_pauseTitle->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 ));
}

void PauseGame:: ProcessInput(){
    while (auto event = m_context->m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>()){
            m_context->m_window->close();
        }
        else if( event->is<sf::Event::KeyPressed>() ){
            if(const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
                {switch (static_cast<sf::Keyboard::Key>(keyEvent->code))
                {
                    case sf::Keyboard::Key::Escape:
                    {
                        m_context->m_state->PopCurrent();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
}
void PauseGame:: Update([[maybe_unused]] sf::Time deltaTime){
    
}

void PauseGame:: Draw(){
    // m_context->m_window->clear(sf::Color::Transparent);
    m_context->m_window->draw(*(m_pauseTitle));
    m_context->m_window->display();
}