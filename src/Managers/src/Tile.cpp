#include "../include/Tile.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <yaml-cpp/exceptions.h>

Tile::Tile() {
  this->shape = new sf::RectangleShape;
  this->shape->setFillColor(sf::Color::White);
  this->shape->setSize(sf::Vector2f(100, 100));
}

void Tile::update(sf::RenderWindow *window) {
  if (isAnimated == true) {
    if (this->clock->getElapsedTime().asMilliseconds() >
        this->textures.intervalMs) {
      this->nextAnimatedTile();
      this->clock->restart();
    }
  }
  window->draw(*this->shape);
}

void Tile::setPosition(sf::Vector2f position) {
  this->shape->setPosition(position);
}

void Tile::nextAnimatedTile() {
  this->textures.textureIndex++;
  if (this->textures.lenTextures <= this->textures.textureIndex) {
    this->textures.textureIndex = 0;
  }
  this->shape->setTextureRect(sf::IntRect(
      sf::Vector2i(100 * ((id + this->textures.textureIndex) % 10),
                   (int)100 * (id + this->textures.textureIndex) / 1000),
      sf::Vector2i(100, 100)));
}

void Tile::setPosition(float x, float y) { this->shape->setPosition(x, y); }

void Tile::setId(int id) { this->id = id; }

void Tile::updateTexture() {
  this->texture = new sf::Texture();
  this->texture->loadFromFile(DEFAULT_TILE_PATH);
  this->shape->setTexture(this->texture);
  this->shape->setTextureRect(
      sf::IntRect(sf::Vector2i(100 * (id % 10), (int)100 * id / 1000),
                  sf::Vector2i(100, 100)));
}

void Tile::updateAnimatedTexture() {
  this->updateTexture();
  this->textures = AnimatedTexture{4, 0, 200};
  *this->textures.textures = new sf::Texture[4];
  this->textures.textures[0] = this->texture;
  for (int i = 1; i < 4; i++) {
    sf::Texture *newText = new sf::Texture();
    newText->loadFromFile(DEFAULT_TILE_PATH);
    this->textures.textures[i] = newText;
  }
}

Tile *loadTileFromFile(YAML::Node node) {
  Tile *tile = new Tile();
  float x = node["x"].as<float>();
  float y = node["y"].as<float>();
  bool isAnimated = false;
  try {
    isAnimated = node["isAnimated"].as<bool>();
  } catch (YAML::Exception) {
    isAnimated = false;
  }

  tile->setPosition(sf::Vector2f(x, y));

  int id = node["id"].as<int>();
  tile->setId(id);
  if (!isAnimated) {
    tile->updateTexture();
  } else {
    tile->updateAnimatedTexture();
    tile->setIsAnimated(true);
  }

  return tile;
}
