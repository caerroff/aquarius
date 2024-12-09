#include "../include/Item.hpp"

Item::Item()
{

}

Item::Item(int id) : Item()
{
    this->id = id;
}

Item::Item(int id, sf::Vector2f position) : Item(id)
{
    this->position = position;
    this->body->setPosition(position);
    this->body->setSize(sf::Vector2f(64, 64));
    this->hitbox->setPosition(position);
    this->hitbox->setSize(sf::Vector2f(64, 64));
    this->hitbox->setFillColor(sf::Color::Transparent);
}

Item::Item(int id, sf::Vector2f position, sf::Texture *texture) : Item(id, position)
{
    this->texture = texture;
    this->body->setOrigin(sf::Vector2f(32, 32));
    this->body->setScale(sf::Vector2f(0.5, 0.5));
    this->body->setTexture(this->texture);
    this->body->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 64)));
}

void Item::update(sf::RenderWindow *window)
{
    this->animate();
    window->draw(*this->body);
}

void Item::animate()
{
    // Make the item body float 50px up and then 50px down
    if (this->body->getPosition().y - 10 < this->hitbox->getPosition().y)
    {
        if (this->animationDirection == DOWN)
        {
            this->body->move(0, 0.5);
        }
    }
    else
    {
        this->animationDirection = UP;
    }

    if (this->body->getPosition().y + 10 > this->hitbox->getPosition().y)
    {
        if (this->animationDirection == UP)
        {
            this->body->move(0, -0.5);
        }
    }
    else
    {
        this->animationDirection = DOWN;
    }
}
