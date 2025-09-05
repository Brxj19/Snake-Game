#include"Snake.hpp"

Snake::Snake() : m_body(4){
    m_head =  --m_body.end();
    m_tail = m_body.begin();
}   

Snake::~Snake(){

}

void Snake::Init(const sf::Texture &texture){
    float x = 16.f;
    for(auto &body : m_body){
        body = std::make_unique<sf::Sprite>(texture);
        // body->setTexture(texture);
        body->setPosition(sf::Vector2f(x,16.f));
        x += 16.f;
    }
}
void Snake::Move(const sf::Vector2f &direction){
    m_tail->get()->setPosition(m_head->get()->getPosition() + direction);
    m_head = m_tail;
    ++m_tail;

    if(m_tail == m_body.end()){
        m_tail = m_body.begin();
    }
}

bool Snake::IsOn(sf::Sprite &other) const {
    return m_head->get()->getGlobalBounds().findIntersection(other.getGlobalBounds()).has_value();
}

bool Snake::isFoodSnakeIntersecting(sf::Sprite &other) const{
    int flag = false;
   for(auto body = m_body.begin(); body != m_body.end(); ++body){
    
        flag = body->get()->getGlobalBounds().findIntersection(other.getGlobalBounds()).has_value();
        if(flag) break;
    }
    return flag;
}

void Snake::Grow(const sf::Vector2f &direction){
    std::unique_ptr<sf::Sprite> newBody = std::make_unique<sf::Sprite>(m_tail->get()->getTexture());
    newBody->setPosition(m_head->get()->getPosition() + direction);
    m_head = m_body.insert(++m_head,std::move(newBody));
}

bool Snake::isSelfIntersecting() const{
   bool flag = false;
   for(auto body = m_body.begin(); body != m_body.end(); ++body){
        if(body != m_head ){
            flag = IsOn(**body);
            if(flag) break;
        }
   }
   return flag;
}

void Snake::draw(sf::RenderTarget& target, [[maybe_unused]]sf::RenderStates states) const{
    for(auto &body : m_body){
        target.draw(*(body));
    }
}

