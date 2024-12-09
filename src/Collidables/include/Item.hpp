#ifndef ITEM
#define ITEM
#include "CollisionEntity.hpp"

class Item : public CollisionEntity
{
private:
    int id;
    sf::Vector2f position;
    sf::Texture *texture;

public:
    void update(sf::RenderWindow *window);

};

#endif