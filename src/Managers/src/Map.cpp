#include "../include/Map.hpp"

Map::Map()
{
  this->size = sf::Vector2f(0, 0);
  this->clearColor = sf::Color(255, 255, 255);
}

Map::Map(sf::Vector2f _size)
{
  this->size = _size;
}

void Map::update(sf::RenderWindow *window)
{
  for (int i = 0; i < this->tiles.size(); i++)
  {
    this->tiles.at(i)->update(window);
  }
  for (int i = 0; i < this->characters.size(); i++)
  {
    this->characters.at(i)->update(window);
  }
}

void Map::addCharacter(Character *character)
{
  this->characters.push_back(character);
}

void Map::removeCharacterAt(int position)
{
  this->characters.erase(this->characters.begin() + position);
}

Character *Map::getCharacterAt(int position)
{
  return this->characters.at(position);
}

void Map::addTile(Tile *tile)
{
  this->tiles.push_back(tile);
}

void Map::removeTileAt(int position)
{
  this->tiles.erase(this->tiles.begin() + position);
}

Tile *Map::getTileAt(int position)
{
  return this->tiles.at(position);
}

Action *Map::getActionAt(int pos)
{
  return this->actions.at(pos);
}

void Map::addAction(Action *action)
{
  this->actions.push_back(action);
}

Map *loadMapFromFile(std::string path)
{
  Map *map = new Map();
  std::cout << "Loading Map at: " << DEFAULT_MAP_PATH << path << std::endl;
  try
  {
    YAML::Node mapFile = YAML::LoadFile(path);

    if (mapFile["Background"].IsSequence() && mapFile["Background"].size() == 3)
    {
      std::vector<int> color = mapFile["Background"].as<std::vector<int>>();
      map->setClearColor(sf::Color(color.at(0), color.at(1), color.at(2)));
    }

    if (mapFile["Music"].IsDefined())
    {
      map->setMusicPath(DEFAULT_MUSIC_PATH + mapFile["Music"].as<std::string>());
    }

    for (auto tileNode : mapFile["Tiles"])
    {
      Tile *tile = loadTileFromFile(tileNode);
      map->addTile(tile);
    }
  }
  catch (YAML::BadConversion e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (YAML::BadFile e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (std::exception e)
  {
    std::cerr << e.what() << std::endl;
  }

  return map;
}