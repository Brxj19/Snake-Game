#pragma once

#include<memory>

#include<SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.hpp"
#include "StateManager.hpp"

enum AssetId{
    MAIN_FONT = 0,
    GRASS,
    FOOD,
    WALL,
    SNAKE
};
using namespace std;
using namespace Engine;

struct Context{
    unique_ptr<AssetManager> m_asset;
    unique_ptr<StateManager> m_state;
    unique_ptr<sf::RenderWindow> m_window;

    Context(){
        m_asset = make_unique<AssetManager>();
        m_state = make_unique<StateManager>();
        m_window = make_unique<sf::RenderWindow>();
    }
};

class Game{
    private:
        shared_ptr<Context> m_context;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f); 
    public:
        Game();
        ~Game();

        void Run();
};

