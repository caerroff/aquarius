#ifndef PLAYER
#define PLAYER
#include "Character.cpp"


class Player : public Character
{
private:
    int isBeingPlayed;

public:
    Player(char *name, int _isBeingPlayed);
    int getIsBeingPlayed() { return this->isBeingPlayed; }
    void setIsBeingPlayer(int _isBeingPlayed) { this->isBeingPlayed = _isBeingPlayed; }
    using Character::update;
    void update(sf::RenderWindow* window) override;
    void handleKeys();
};

#endif