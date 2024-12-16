#include "../include/Player.hpp"

Player::Player(std::string name, int _isBeingPlayed) : Character(name)
{
    keyState.fill(false);
    this->isBeingPlayed = _isBeingPlayed;
    this->getBody()->setFillColor(sf::Color::Red);
}

void Player::update(sf::RenderWindow *window, std::vector<Character *> characters)
{
    if (velocity.x && velocity.y)
    {
        if (abs(velocity.x) > 5 * sqrt(2))
        {
            if (velocity.x > 0)
                velocity.x = 5 * sqrt(2);
            else
                velocity.x = -(5 * sqrt(2));
        }

        if (abs(velocity.y) > 5 * sqrt(2))
        {
            if (velocity.y > 0)
                velocity.y = 5 * sqrt(2);
            else
                velocity.y = -(5 * sqrt(2));
        }
    }
    this->getBody()->move(velocity);
    if (velocity.x != 0 || velocity.y != 0)
    {
        sf::View tempView = window->getView();
        tempView.setCenter(this->getBody()->getPosition());
        window->setView(tempView);
    }

    velocity.x = (int)velocity.x;
    velocity.y = (int)velocity.y;
    if (velocity.x > 0)
        velocity.x--;
    if (velocity.x < 0)
        velocity.x++;
    if (velocity.y > 0)
        velocity.y--;
    if (velocity.y < 0)
        velocity.y++;

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::I))
    {
        keyState[sf::Keyboard::I] = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I) && ! keyState[sf::Keyboard::I])
    {
        keyState[sf::Keyboard::I] = true;
        if(currentState != State::INVENTORY_STATE)
        {
        this->currentState = State::INVENTORY_STATE;
        }
        else
        {
            this->currentState = State::AFK;
        }
    }

    if (this->getCurrentState() == State::AFK)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->velocity = sf::Vector2f(velocity.x, 6);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->velocity = sf::Vector2f(velocity.x, -6);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->velocity = sf::Vector2f(-6, velocity.y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->velocity = sf::Vector2f(6, velocity.y);
        }
    }
    Character::update(window);
}

void Player::handleKeys()
{
    ;
}

void Player::updateSpriteInfos()
{
    Character::updateSpriteInfos();
}

void Player::loadSprite(std::string path, sf::Vector2i size)
{
    Character::loadSprite(path, size);
}