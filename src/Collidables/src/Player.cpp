#include "../include/Player.hpp"

Player::Player(std::string name, int _isBeingPlayed) : Character(name)
{
    this->isBeingPlayed = _isBeingPlayed;
    this->getBody()->setFillColor(sf::Color::Red);
}

void Player::update(sf::RenderWindow *window)
{
    // 10 = a^2 + b^2
    // 5*sqrt(2)
    // 100 = 10^2 + 10^2
    if (velocity.x && velocity.y)
    {
        if (abs(velocity.x) > 5 * sqrt(2))
        {
            if(velocity.x > 0)
                velocity.x = 5 * sqrt(2);
            else
                velocity.x = -(5 * sqrt(2));
        }

        if (abs(velocity.y) > 5 * sqrt(2))
        {
            if(velocity.y > 0)
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->velocity = sf::Vector2f(velocity.x, 10);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->velocity = sf::Vector2f(velocity.x, -10);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->velocity = sf::Vector2f(-10, velocity.y);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->velocity = sf::Vector2f(10, velocity.y);
    }
    window->draw(*this->getBody());
}

void Player::handleKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->getBody()->move(sf::Vector2f(0, -2));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->getBody()->move(sf::Vector2f(0, 2));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->getBody()->move(sf::Vector2f(2, 0));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->getBody()->move(sf::Vector2f(-2, 0));
}