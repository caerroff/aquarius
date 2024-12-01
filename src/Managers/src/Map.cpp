#include "../include/Map.hpp"

Map::Map(sf::RenderWindow *window)
{
  this->size = sf::Vector2f(0, 0);
  this->clearColor = sf::Color(255, 255, 255);
  this->view = new sf::View();
  this->view->setCenter(sf::Vector2f(0, 0));
  this->view->setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

Map::Map(sf::RenderWindow *window, sf::Vector2f _size) : Map(window)
{
  this->size = _size;
}

void Map::update(sf::RenderWindow *window)
{
  window->setView(*this->view);
  for (int i = 0; i < this->tiles.size(); i++)
  {
    if (viewContains(this->tiles.at(i)->getPosition(), this->tiles.at(i)->getSize()))
    {
      std::cout << "Rendered tile at : " << i << std::endl;
      this->tiles.at(i)->update(window);
    }
    else
    {
      std::cout << "Didn't render the tile at : " << i << std::endl;
    }
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

Map *loadMapFromFile(std::string path, sf::RenderWindow *window)
{
  Map *map = new Map(window);
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

bool Map::viewContains(sf::Vector2f position, sf::Vector2f size)
{
  if (position.x < view->getCenter().x - view->getSize().x / 2 - (size.x + 50))
  {
    return false;
  }

  if (position.x > view->getCenter().x + view->getSize().x / 2 + 50)
  {
    return false;
  }

  if (position.y < view->getCenter().y - view->getSize().y / 2 - (size.y + 50))
  {
    return false;
  }

  if (position.y > view->getCenter().y + view->getSize().y / 2 + 50)
  {
    return false;
  }

  return true;
}