#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>

class Button
{
  private:
    sf::RectangleShape *rectangle;
    sf::Text *text;
    sf::Color *outlineColor;
    
  public:
    Button(std::string text, sf::Vector2f position, int margin, int size, std::string font);
    void setOutlineColor(int r, int g, int b);
};

#endif