#include "../include/Animation.hpp"

void Animation::update(Character* character)
{
    if(character->getVelocity().x < 0)
    {
        // Turn the sprite to the left;
    }
    else if (character->getVelocity().x > 0)
    {
        // Turn the sprite to the right;
    }

    if(character->getVelocity().y > 0)
    {
        // Turn the sprite up;
    }
    else if (character->getVelocity().y < 0)
    {
        // Turn the sprite down;
    }
}