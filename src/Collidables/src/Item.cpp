#include "../include/Item.hpp"

void Item::update(sf::RenderWindow *window)
{
    this->texture = new sf::Texture();
    this->body->setTexture(texture);
    window->draw(*this->body);
}