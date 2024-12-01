#include "../include/Tile.hpp"

Tile::Tile()
{
  this->shape = new sf::RectangleShape;
  this->shape->setFillColor(sf::Color::White);
  this->shape->setSize(sf::Vector2f(100,100));
}

void Tile::update(sf::RenderWindow *window)
{
  window->draw(*this->shape);
}

void Tile::setPosition(sf::Vector2f position)
{
  this->shape->setPosition(position);
}

void Tile::setPosition(float x, float y)
{
  this->shape->setPosition(x, y);
}

void Tile::setId(int id)
{
  this->id = id;
}

void Tile::updateTexture()
{
  ;
}

Tile *loadTileFromFile(YAML::Node node)
{
  Tile *tile = new Tile();
  float x = node["x"].as<float>();
  float y = node["y"].as<float>();

  tile->setPosition(sf::Vector2f(x, y));

  int id = node["id"].as<int>();
  tile->setId(id);
  tile->updateTexture();
  
  return tile;
}