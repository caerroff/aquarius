#ifndef INVENTORY
#define INVENTORY
#include <SFML/Graphics.hpp>
#include "../../Collidables/include/Collidables.hpp"
#include <string>
#include <vector>

class Inventory
{
private:
    Player *player;
    sf::RectangleShape *virtualWindow;
    Inventory(sf::RenderWindow *window);
    sf::RenderWindow *window;
    sf::Font *font;
    std::vector<sf::Text> texts;
    sf::ConvexShape *selector;

public:
    Inventory(Player *player, sf::RenderWindow *window);
    void render();
    void update();
    void _createVirtualWindow(sf::RenderWindow *window);
};

#endif