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

struct Flags{
  bool shouldSortEntities = false;
};

class Map
{
private:
  sf::Vector2f size;
  sf::View *view;
  sf::Vector2f viewVelocity;
  std::vector<Character *> characters;
  std::vector<Tile *> tiles;
  std::vector<Action *> actions;
  std::string musicPath;
  sf::Color clearColor;
  Map *nextMap;
  Player* player;
  const char *name;
  std::array<bool, sf::Keyboard::KeyCount> keyState;
  bool viewContains(sf::Vector2f position, sf::Vector2f size);
  std::vector<CollisionEntity *> entities;

  /**
   * @brief Private method sorting the entities from smallest to highest y position
   */
  void _sortEntities();

public:
  Flags flags;
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
  std::vector<Tile *> getTiles(){return this->tiles;}
  void setClearColor(sf::Color _clearColor) { this->clearColor = _clearColor; }
  sf::Color getClearColor() { return this->clearColor; }
  Action *getActionAt(int pos);
  void addAction(Action *action);
  Character *loadCharacterFromFile(YAML::Node node);
  int getActionCount() { return this->actions.size(); }

  void setPlayer(Player* player) { this->player = player;}
  Player* getPlayer(){return this->player;}

  sf::View *getView() { return this->view; }

  void setViewVelocity(sf::Vector2f velocity);
  sf::Vector2f getViewVelocity(){return this->viewVelocity;}

  Flags getFlags(){return this->flags;}
};

Map *loadMapFromFile(std::string path, sf::RenderWindow *window);

#endif