#ifndef PLAYER
#define PLAYER
#include "Character.hpp"
#include <iostream>
#include <math.h>
#include "Item.hpp"

class Player : public Character
{

private:
    int isBeingPlayed;
    std::vector<Item *> items;
    std::array<bool, sf::Keyboard::KeyCount> keyState;

public:
    Player(std::string name, int _isBeingPlayed);
    int getIsBeingPlayed() { return this->isBeingPlayed; }
    void setIsBeingPlayer(int _isBeingPlayed) { this->isBeingPlayed = _isBeingPlayed; }
    void update(sf::RenderWindow *window, std::vector<Character *> characters);
    void handleKeys();

    void loadSprite(std::string path, sf::Vector2i size = sf::Vector2i(64, 64));
    void updateSpriteInfos();

    void addItemToInventory(Item* item){ this->items.push_back(item);}
    std::vector<Item *> getAllItems(){return this->items;}
    Item* getItemAt(int position){return this->items.at(position);}
};

#endif