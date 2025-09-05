#include"GamePlay.hpp"
#include"GameOver.hpp"
#include"PauseGame.hpp"

#include<SFML/Graphics/Rect.hpp>

#include<stdlib.h>
#include<time.h>

GamePlay::GamePlay(std::shared_ptr<Context> &context) : m_context(context),
                                                        m_snakeDirection({16.f,0.f}),
                                                        m_elapsedTime(sf::Time::Zero),
                                                        m_score(0),
                                                        m_isPaused(false)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{

}

void GamePlay::Init(){
    m_context->m_asset->AddTexture(GRASS,"./assets/textures/grass.png",true);
    m_context->m_asset->AddTexture(FOOD,"./assets/textures/food.png");
    m_context->m_asset->AddTexture(WALL,"./assets/textures/wall.png",true);
    m_context->m_asset->AddTexture(SNAKE,"./assets/textures/snake.png");

    m_grass = std::make_unique<sf::Sprite>(m_context->m_asset->getTexture(GRASS));
    m_grass->setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for(auto & wall : m_walls){
        wall = std::make_unique<sf::Sprite>(m_context->m_asset->getTexture(WALL));
    }
    sf::Vector2u windowSize = m_context->m_window->getSize();
    m_walls[0]->setTextureRect(sf::IntRect{{0, 0}, {static_cast<int>(windowSize.x), 16}});

    m_walls[1]->setTextureRect(sf::IntRect{{0, 0}, {static_cast<int>(windowSize.x), 16}});
    m_walls[1]->setPosition(sf::Vector2f(0,static_cast<int>(windowSize.y - 16)));

    m_walls[2]->setTextureRect(sf::IntRect{{0, 0}, {16, static_cast<int>(windowSize.y)}});

    m_walls[3]->setTextureRect(sf::IntRect{{0, 0}, {16, static_cast<int>(windowSize.y)}});
    m_walls[3]->setPosition(sf::Vector2f(static_cast<int>(windowSize.x - 16), 0));

    m_food = std::make_unique<sf::Sprite>(m_context->m_asset->getTexture(FOOD));
    // m_food->setTextureRect(sf::IntRect{{0,0}, {32,32}});
    m_food->setPosition(sf::Vector2f(static_cast<int>(windowSize.x / 2), static_cast<int>(windowSize.y / 2)));

    m_snake.Init(m_context->m_asset->getTexture(SNAKE));

    m_scoreText = std::make_unique<sf::Text>(m_context->m_asset->getFont(MAIN_FONT),"Score : "+std::to_string(m_score),16);
    // m_scoreText->setFillColor(sf::Color::White);
    // sf::FloatRect bounds = m_scoreText->getLocalBounds();
    // m_scoreText->setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,bounds.position.y + bounds.size.y / 2.0f));
    m_scoreText->setPosition(sf::Vector2f(0,0));
}

void GamePlay::ProcessInput(){
    while (auto event = m_context->m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>()){
            m_context->m_window->close();
        }
        else if( event->is<sf::Event::KeyPressed>() ){
            sf::Vector2f newDirection = m_snakeDirection;
            if(const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()){
                

                switch (static_cast<sf::Keyboard::Key>(keyEvent->code))
                {

                    case sf::Keyboard::Key::Up:
                        // if(m_snakeDirection.y == 0.f)
                            newDirection = {0.f,-16.f};
                        break;
                    case sf::Keyboard::Key::Down:
                        // if(m_snakeDirection.y == 0.f)
                            newDirection = {0.f,16.f};
                        break;
                    case sf::Keyboard::Key::Left:
                        // if(m_snakeDirection.x == 0.f)
                            newDirection = {-16.f,0.f};
                        break;
                    case sf::Keyboard::Key::Right:
                        // if(m_snakeDirection.x == 0.f) 
                            newDirection = {16.f,0.f};
                        break;
                    case sf::Keyboard::Key::W:
                        // if(m_snakeDirection.y == 0.f)
                            newDirection = {0.f,-16.f};
                        break;
                    case sf::Keyboard::Key::S:
                        // if(m_snakeDirection.y == 0.f)
                            newDirection = {0.f,16.f};
                        break;
                    case sf::Keyboard::Key::A:
                        // if(m_snakeDirection.x == 0.f)
                            newDirection = {-16.f,0.f};
                        break;
                    case sf::Keyboard::Key::D:
                        // if(m_snakeDirection.x == 0.f) 
                            newDirection = {16.f,0.f};
                        break;
                    case sf::Keyboard::Key::Escape:
                        //pause logic
                        m_context->m_state->Add(std::make_unique<PauseGame>(m_context));
                        break;
                    default:
                        break;

                }
                if(std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || std::abs(m_snakeDirection.y) != std::abs(newDirection.y)){
                    m_snakeDirection = newDirection;
                }
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime){
    if(!m_isPaused){
        m_elapsedTime += deltaTime;
        if(m_elapsedTime.asSeconds() > 12.f){

            bool isOnWall = false;

            for(auto &wall : m_walls){
                if(m_snake.IsOn(*wall)){
                    isOnWall = true;
                    m_context->m_state->Add(std::make_unique<GameOver>(m_context), isOnWall);
                    break;
                }

            }
            if(m_snake.IsOn(*m_food)){
                m_snake.Grow(m_snakeDirection);

                int x = 0;
                int y = 0;

                x = rand() % m_context->m_window->getSize().x;
                y = rand() % m_context->m_window->getSize().y;
                x = std::clamp<int>(x,16, m_context->m_window->getSize().x-32);
                y = std::clamp<int>(y,16, m_context->m_window->getSize().y-32);

                m_food->setPosition(sf::Vector2f(x - x%16,y - y%16));

                m_score += 1;
                m_scoreText->setString("Score : "+std::to_string(m_score));
            }
            else if(m_snake.isFoodSnakeIntersecting(*m_food)){
                int x = 0;
                int y = 0;

                x = rand() % m_context->m_window->getSize().x;
                y = rand() % m_context->m_window->getSize().y;
                x = std::clamp<int>(x,16, m_context->m_window->getSize().x-32);
                y = std::clamp<int>(y,16, m_context->m_window->getSize().y-32);

                m_food->setPosition(sf::Vector2f(x - x%16,y - y%16));
            }
            else{
                m_snake.Move(m_snakeDirection);
            }

            if(m_snake.isSelfIntersecting()){
                isOnWall = true;
                m_context->m_state->Add(std::make_unique<GameOver>(m_context), isOnWall);
            }
            m_elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw(){
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(*m_grass);
    for(auto &wall : m_walls){
        m_context->m_window->draw(*wall);
    }
    m_context->m_window->draw(*m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(*m_scoreText);
    m_context->m_window->display();
}


void GamePlay::Pause(){
    m_isPaused = true;
}

void GamePlay::Start(){
    m_isPaused = false;
}
