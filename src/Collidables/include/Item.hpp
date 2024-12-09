#ifndef ITEM
#define ITEM
#include "CollisionEntity.hpp"
#include <iostream>

enum AnimationDirection
{
    UP,
    DOWN
};

class Item : public CollisionEntity
{
private:
    int id;
    sf::Vector2f position;
    sf::Texture *texture;
    AnimationDirection animationDirection = AnimationDirection::UP;

public:
    // Constructors
    Item();
    Item(int id);
    Item(int id, sf::Vector2f position);
    Item(int id, sf::Vector2f position, sf::Texture *texture);

    void update(sf::RenderWindow *window);
    void animate();
};

#endif