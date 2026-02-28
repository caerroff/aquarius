#ifndef TILE
#define TILE
#include "AnimatedTexture.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <yaml-cpp/yaml.h>
#define DEFAULT_TILE_PATH "assets/tiles/tiles.png"

class Tile
{
private:
  int id;
  sf::RectangleShape *shape;
  sf::Texture *texture;
  bool isAnimated;
  sf::Clock *clock = new sf::Clock();
  AnimatedTexture textures;

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
  void updateAnimatedTexture();
  void nextAnimatedTile();
  void setIsAnimated(bool value) {this->isAnimated = value;}
};

Tile *loadTileFromFile(YAML::Node node);

#endif
