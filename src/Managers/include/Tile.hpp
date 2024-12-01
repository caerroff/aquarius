#ifndef TILE
#define TILE
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>

class Tile
{
private:
  int id;
  sf::RectangleShape *shape;
  sf::Texture *texture;

public:
  Tile();
  void update(sf::RenderWindow *window);
  void setPosition(sf::Vector2f position);
  sf::Vector2f getPosition(){return this->shape->getPosition();}
  sf::Vector2f getSize(){return this->shape->getSize();}
  void setPosition(float x, float y);

  void setId(int id);
  int getId(){return id;}

  void updateTexture();
};

Tile *loadTileFromFile(YAML::Node node);

#endif