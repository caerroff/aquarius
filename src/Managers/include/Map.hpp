#ifndef MAP
#define MAP
#include <SFML/Graphics.hpp>
#include "../../UI/include/UI.hpp"
#include "../../Collidables/include/Collidables.hpp"
#include <yaml-cpp/yaml.h>
#include "Scene.hpp"
#include "Tile.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#define DEFAULT_MUSIC_PATH "assets/music/"
#define DEFAULT_SPRITE_PATH "assets/sprites/"
#define DEFAULT_TILES_PATH "assets/tiles/"
#define DEFAULT_FONT_PATH "assets/fonts/PressStart2P-Regular.ttf"
#define DEFAULT_MAP_PATH "assets/maps/"

class Map
{
private:
  sf::Vector2f size;
  sf::View *view;
  std::vector<Character *> characters;
  std::vector<Tile *> tiles;
  std::vector<Action *> actions;
  std::string musicPath;
  sf::Color clearColor;
  Map *nextMap;
  const char *name;
  bool viewContains(sf::Vector2f position, sf::Vector2f size);

public:
  Map(sf::RenderWindow *window);
  Map(sf::RenderWindow *window, sf::Vector2f _size);
  sf::Vector2f getSize() { return this->size; }
  void setSize(sf::Vector2f _size) { this->size = _size; }
  void update(sf::RenderWindow *window);
  void addCharacter(Character *character);
  void removeCharacterAt(int position);
  Character *getCharacterAt(int position);
  int getCharacterCount() { return this->characters.size(); }
  void addTile(Tile *tile);
  void removeTileAt(int position);
  Tile *getTileAt(int position);
  const char *getName() { return this->name; }
  void setName(const char *_name) { this->name = _name; }
  void setMusicPath(std::string _musicPath) { this->musicPath = _musicPath; }
  std::string getMusicPath() { return this->musicPath; }
  void setClearColor(sf::Color _clearColor) { this->clearColor = _clearColor; }
  sf::Color getClearColor() { return this->clearColor; }
  Action *getActionAt(int pos);
  void addAction(Action *action);
  int getActionCount() { return this->actions.size(); }

  sf::View *getView() { return this->view; }
};

Map *loadMapFromFile(std::string path, sf::RenderWindow *window);

#endif