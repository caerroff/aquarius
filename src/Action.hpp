#ifndef ACTION
#define ACTION
#include <SFML/Graphics.hpp>

enum Type
{
    UNDEFINED,
    ActionTextBox,
    ActionMove,
    ActionChangeMap,
    ActionChangeMode
};

class Action
{
private:
    long beginTime;
    long endTime;
    int type;

public:
    Action();
    void setType(Type _type);
    void update(sf::RenderWindow *window, long currentTime);
};

#endif