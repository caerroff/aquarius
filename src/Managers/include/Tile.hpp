#ifndef TILE
#define TILE
#include <SFML/Graphics.hpp>

class Tile{
    private:
        sf::RectangleShape* shape;

    public:
        Tile();
        void update(sf::RenderWindow* window);
};

#endif