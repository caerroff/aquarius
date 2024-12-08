#ifndef PLAYER
#define PLAYER
#include "Character.hpp"
#include <iostream>
#include <math.h>

class Player : public Character
{

private:
    int isBeingPlayed;

public:
    Player(std::string name, int _isBeingPlayed);
    int getIsBeingPlayed() { return this->isBeingPlayed; }
    void setIsBeingPlayer(int _isBeingPlayed) { this->isBeingPlayed = _isBeingPlayed; }
    using Character::update;
    void update(sf::RenderWindow *window);
    void handleKeys();

    void loadSprite(std::string path, sf::Vector2i size = sf::Vector2i(64, 64));
    void updateSpriteInfos();
};

#endif