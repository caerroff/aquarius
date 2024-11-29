#ifndef PLAYER
#define PLAYER
#include "Character.hpp"


class Player : public Character
{
private:
    int isBeingPlayed;

public:
    Player(const char *name, int _isBeingPlayed);
    int getIsBeingPlayed() { return this->isBeingPlayed; }
    void setIsBeingPlayer(int _isBeingPlayed) { this->isBeingPlayed = _isBeingPlayed; }
    using Character::update;
    void update(sf::RenderWindow* window) override;
    void handleKeys();
};

#endif