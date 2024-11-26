#include "Player.hpp"

Player::Player(const char *name, int _isBeingPlayed)
{
    this->setName(name);
    this->isBeingPlayed = _isBeingPlayed;
}

void Player::update(sf::RenderWindow* window)
{
    this->handleKeys();
    this->getBody()->setTexture(this->getSprites()[0]);
    window->draw(*this->getBody());
}

void Player::handleKeys()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->getBody()->move(sf::Vector2f(0, -2));
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->getBody()->move(sf::Vector2f(0,2));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->getBody()->move(sf::Vector2f(2, 0));
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->getBody()->move(sf::Vector2f(-2,0));
}