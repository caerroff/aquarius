#include "Action.hpp"

Action::Action()
{
    this->type = UNDEFINED;
}

void Action::update(sf::RenderWindow* window, long currentTime)
{
    // Step One : Check that the action isn't over yet and that it had started
    if(currentTime > this->endTime || currentTime < this->beginTime)
    {
        return;
    }

    // Step Two : render the action
    switch(type)
    {
        case Type::ActionTextBox:
            break;
        case Type::ActionChangeMap:
            break;
        case Type::ActionMove:
            break;
        case Type::ActionChangeMode:
            break;
        case Type::UNDEFINED:
            break;
        default:
            fprintf(stderr, "Unknown Action type %d \n", type);
            return;
    }
}

void Action::setType(Type type)
{
    this->type = type;
}