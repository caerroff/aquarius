#include "Map.hpp"


Map::Map()
{
    this->size = sf::Vector2f(0, 0);
    this->clearColor = new sf::Color(255, 255, 255);
}

Map::Map(sf::Vector2f _size)
{
    this->size = _size;
}

void Map::update(sf::RenderWindow* window)
{
    for (int i = 0; i < this->characters.size(); i++)
    {
        this->characters.at(i)->update(window);
    }

    
}

void Map::addCharacter(Character * character)
{
    this->characters.push_back(character);
}

void Map::removeCharacterAt(int position)
{
    this->characters.erase(this->characters.begin() + position);
}

Character* Map::getCharacterAt(int position)
{
    return this->characters.at(position);
}

void Map::addTile(Tile* tile)
{
    this->tiles.push_back(tile);
}

void Map::removeTileAt(int position)
{
    this->tiles.erase(this->tiles.begin() + position);
}

Tile* Map::getTileAt(int position)
{
    return this->tiles.at(position);
}

Action* Map::getActionAt(int pos){
    return this->actions.at(pos);
}

void Map::addAction(Action* action)
{
    this->actions.push_back(action);
}

