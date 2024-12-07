#ifndef ANIMATION
#define ANIMATION
#include <SFML/System.hpp>
#include "Character.hpp"
#include "Player.hpp"

class Animation
{
private:
    sf::Clock clock = sf::Clock();
public:
    /*
    * Default constructor
    */
    Animation(){;}

    /**
     * @brief Updates the animation of the Character object.
     * Changes the sprites accordingly, handles right and left facing.
     * @param character a pointer to the Character object.
     */
    void update(Character *character);

};

#endif