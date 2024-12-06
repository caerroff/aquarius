#ifndef PLAYER
#define PLAYER
#include "Character.hpp"
#include <iostream>


class Player : public Character
{
private:
    int isBeingPlayed;
    sf::Vector2f velocity;

public:
    Player(std::string name, int _isBeingPlayed);
    int getIsBeingPlayed() { return this->isBeingPlayed; }
    void setIsBeingPlayer(int _isBeingPlayed) { this->isBeingPlayed = _isBeingPlayed; }
    using Character::update;
    void update(sf::RenderWindow* window);
    void handleKeys();
};

#endif