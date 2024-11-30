#include "../include/Tile.hpp"

Tile::Tile()
{
  this->shape = new sf::RectangleShape;
}

void Tile::update(sf::RenderWindow *window)
{
  window->draw(*this->shape);
}