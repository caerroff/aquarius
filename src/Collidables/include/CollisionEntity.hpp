#ifndef COLLISIONENTITY
#define COLLISIONENTITY
#include <SFML/Graphics.hpp>

class CollisionEntity
{
    private:
        sf::RectangleShape hitbox;
        sf::RectangleShape body;
        sf::Vector2f size;
        bool renderable;

    public:
        virtual bool isRenderable(){return this->renderable;}
        virtual void setRenderable(bool _renderable){this->renderable = _renderable;}
        sf::Vector2f getSize(){return this->size;}
        void setSize(int x, int y){this->size = sf::Vector2f(x, y);}
        void setSize(sf::Vector2f size){this->size = size;}
};


#endif