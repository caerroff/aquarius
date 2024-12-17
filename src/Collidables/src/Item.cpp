#include "../include/Item.hpp"

Item::Item()
{
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("assets/sprites/Items/items.png");
    this->texture = texture;
    this->body->setSize(sf::Vector2f(64, 64));
    this->hitbox->setSize(sf::Vector2f(64, 64));
    this->hitbox->setFillColor(sf::Color::Transparent);
    this->body->setOrigin(sf::Vector2f(32, 32));
    this->body->setScale(sf::Vector2f(0.5, 0.5));
    this->body->setTexture(this->texture);
    this->body->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 64)));
}

Item::Item(int id) : Item()
{
    this->id = id;
    std::cout << "Top " <<  (int) (((this->id - 1) * 64) / this->texture->getSize().x) <<  std::endl;
    std::cout << "Left " << (this->id - 1) * 64 << std::endl;
    this->body->setTextureRect(sf::IntRect(sf::Vector2i((this->id - 1) * 64, (int) (((this->id - 1) * 64) / this->texture->getSize().x)), sf::Vector2i(64, 64)));
}

Item::Item(int id, sf::Vector2f position) : Item(id)
{
    this->position = position;
    this->body->setPosition(position);
    this->hitbox->setPosition(position);
}

void Item::setPosition(sf::Vector2f position)
{
    this->body->setPosition(position);
    this->hitbox->setPosition(position);
}

Item::Item(int id, sf::Vector2f position, sf::Texture *texture) : Item(id, position)
{
    this->texture = texture;
}

void Item::update(sf::RenderWindow *window)
{
    this->animate();
}

void Item::animate()
{
    // Make the item body float 50px up and then 50px down
    if (this->body->getPosition().y - 5 < this->hitbox->getPosition().y)
    {
        if (this->animationDirection == DOWN)
        {
            this->body->move(0, 0.2);
        }
    }
    else
    {
        this->animationDirection = UP;
    }

    if (this->body->getPosition().y + 5 > this->hitbox->getPosition().y)
    {
        if (this->animationDirection == UP)
        {
            this->body->move(0, -0.2);
        }
    }
    else
    {
        this->animationDirection = DOWN;
    }
}
