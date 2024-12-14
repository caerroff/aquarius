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
    std::string name;

public:
    // Constructors
    Item();
    Item(int id);
    Item(int id, sf::Vector2f position);
    Item(int id, sf::Vector2f position, sf::Texture *texture);

    void update(sf::RenderWindow *window);
    void animate();

    void setName(std::string name) { this->name = name; }
    std::string getName() { return this->name; }

    int getId() { return this->id ;}
};

#endif