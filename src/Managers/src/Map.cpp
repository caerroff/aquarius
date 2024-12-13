#include "../include/Map.hpp"

Map::Map(sf::RenderWindow *window)
{
  this->size = sf::Vector2f(0, 0);
  this->clearColor = sf::Color(255, 255, 255);
  this->view = new sf::View();
  this->view->setCenter(sf::Vector2f(0, 0));
  this->view->setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
  keyState.fill(false);
}

Map::Map(sf::RenderWindow *window, sf::Vector2f _size) : Map(window)
{
  this->size = _size;
}

void Map::update(sf::RenderWindow *window)
{
  if (this->flags.shouldSortEntities)
  {
    // We should do the z-sort here
    _sortEntities();
  }
  view->move(viewVelocity);
  window->setView(*this->view);

  // Slow the view until it's back to 0
  viewVelocity.x = (int)viewVelocity.x;
  viewVelocity.y = (int)viewVelocity.y;
  if (viewVelocity.x > 0)
    viewVelocity.x--;
  if (viewVelocity.x < 0)
    viewVelocity.x++;
  if (viewVelocity.y > 0)
    viewVelocity.y--;
  if (viewVelocity.y < 0)
    viewVelocity.y++;

  for (int i = 0; i < this->tiles.size(); i++)
  {
    if (viewContains(this->tiles.at(i)->getPosition(), this->tiles.at(i)->getSize()))
    {
      this->tiles.at(i)->update(window);
    }
  }
  for (int i = 0; i < this->characters.size(); i++)
  {
    this->characters.at(i)->update(window);
  }

  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
  {
    keyState[sf::Keyboard::E] = false;
  }

  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    keyState[sf::Keyboard::Space] = false;
  }

  for (auto character : characters)
  {
    if(!viewContains(character->getPosition(), character->getSize()))
    {
      continue;
    }
    if (character->getBody()->getGlobalBounds().intersects(this->player->getBody()->getGlobalBounds()))
    {
      if (!keyState[sf::Keyboard::E] && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && character->getCurrentState() != State::TALKING)
      {
        keyState[sf::Keyboard::E] = true;
        // Call the dialogue of this character
        character->dialogue(window);
        player->setCurrentState(State::TALKING);
      }
      if (!keyState[sf::Keyboard::E] && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && character->getCurrentState() == State::TALKING)
      {
        keyState[sf::Keyboard::E] = true;
        character->skipDialogue();
        player->setCurrentState(State::AFK);
      }

      if (!keyState[sf::Keyboard::Space] && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && character->getCurrentState() == State::TALKING)
      {
        keyState[sf::Keyboard::Space] = true;
        character->skipDialogue();
        player->setCurrentState(State::AFK);
      }
      character->getBody()->setFillColor(sf::Color::Red);
    }
    else
    {
      character->getBody()->setFillColor(sf::Color::White);
    }
  }
  this->player->update(window, characters);
  for (auto entity : entities)
  {
    if (viewContains(entity->getPosition(), entity->getSize()))
    {
      entity->render(window);
    }
  }
  this->view->setCenter(window->getView().getCenter());
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

    if (mapFile["Characters"].IsDefined())
    {
      for (YAML::Node characterNode : mapFile["Characters"])
      {
        Character *character = map->loadCharacterFromFile(characterNode);
        if (dynamic_cast<Player *>(character) != nullptr)
        {
          // We know we have a player object
          map->setPlayer(dynamic_cast<Player *>(character));
        }
        else
        {
          // We don't have a player, so we must be having a character
          map->addCharacter(character);
        }
      }
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
  map->flags.shouldSortEntities = true;
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

void Map::setViewVelocity(sf::Vector2f velocity)
{
  this->viewVelocity.x = velocity.x;
  this->viewVelocity.y = velocity.y;
}

Character *Map::loadCharacterFromFile(YAML::Node node)
{
  if (node["isPlayer"].IsDefined() && node["isPlayer"].as<bool>() == true)
  {
    // We create a Player object instead of a Character
    Player *player = new Player(node["Name"].as<std::string>(), true);
    player->loadSprite(node["sprites"].as<std::string>());
    player->setPosition(sf::Vector2f(node["x"].as<float>(), node["y"].as<float>()));
    entities.push_back(player);
    return player;
  }

  Character *character = new Character();
  character->setPosition(sf::Vector2f(node["x"].as<float>(), node["y"].as<float>()));
  entities.push_back(character);
  return character;
}

void Map::_sortEntities()
{
  if (entities.size() < 2)
  {
    return;
  }
  for (int i = 0; i < entities.size() - 1; i++)
  {
    CollisionEntity *pt1 = entities.at(i);
    for (int j = i + 1; j < entities.size(); j++)
    {
      CollisionEntity *pt2 = entities.at(j);
      if (pt2->getPosition().y < pt1->getPosition().y)
      {
        std::swap(entities[i], entities[j]);
      }
    }
  }
}
