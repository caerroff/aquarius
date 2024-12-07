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
    void update(sf::RenderWindow* window);
    void handleKeys();
};

#endif