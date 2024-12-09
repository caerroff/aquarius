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
  // Infos
  sf::Vector2f size;
  std::string musicPath;
  sf::Color clearColor;
  const char *name;
  Map *nextMap;
  
  // Camera and rendering utilities
  sf::Vector2f viewVelocity;
  sf::View *view;
  bool viewContains(sf::Vector2f position, sf::Vector2f size);

  // Vectors
  std::vector<Character *> characters;
  std::vector<Tile *> tiles;
  std::vector<Action *> actions;
  std::vector<Item *> items;

  // Misc
  std::array<bool, sf::Keyboard::KeyCount> keyState;
  Player *player;
  
public:
  // Constructors
  Map(sf::RenderWindow *window);
  Map(sf::RenderWindow *window, sf::Vector2f _size);

  // Useful methods
  /**
   * @brief updates the map and calls the update method of all objects it contains,
   * including characters, player, items, tiles etc...
   * @param window the window we want to render the map to.
   */
  void update(sf::RenderWindow *window);

  /**
   * @brief loads the Character OR Player from a YAML file using yaml-cpp
   * @param node The node (yaml-cpp object) containing all informations about the player.
   * @return A pointer to the loaded Character or Player (polymorphism).
   */
  Character *loadCharacterFromFile(YAML::Node node);

  // Getters
  sf::Vector2f getSize() { return this->size; }
  Character *getCharacterAt(int position);
  int getCharacterCount() { return this->characters.size(); }
  Tile *getTileAt(int position);
  std::string getMusicPath() { return this->musicPath; }
  const char *getName() { return this->name; }
  std::vector<Tile *> getTiles() { return this->tiles; }
  sf::Color getClearColor() { return this->clearColor; }
  int getActionCount() { return this->actions.size(); }
  Player *getPlayer() { return this->player; }
  sf::View *getView() { return this->view; }
  sf::Vector2f getViewVelocity() { return this->viewVelocity; }
  Item *getItemAt(int index) { return this->items.at(index); }
  std::vector<Item *> getItems() { return this->items; }
  Action *getActionAt(int pos);

  // Adders
  void addCharacter(Character *character);
  void addTile(Tile *tile);
  void addAction(Action *action);
  void addItem(Item *item) { this->items.push_back(item); }

  // Setters
  void setSize(sf::Vector2f _size) { this->size = _size; }
  void removeCharacterAt(int position);
  void removeTileAt(int position);
  void setName(const char *_name) { this->name = _name; }
  void setMusicPath(std::string _musicPath) { this->musicPath = _musicPath; }
  void setClearColor(sf::Color _clearColor) { this->clearColor = _clearColor; }
  void setPlayer(Player *player) { this->player = player; }
  void setViewVelocity(sf::Vector2f velocity);
};

/**
 * @brief loads a map from the specified file and passes it the window 
 * argument which the map will use as default rendering target.
 * @param path The path to the YAML file containing the map (can be relative or absolute)
 * @param window A pointer to the window that will be given to the created Map
 * @return A pointer to the created Map object
 */
Map *loadMapFromFile(std::string path, sf::RenderWindow *window);

#endif