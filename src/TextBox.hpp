#ifndef TEXTBOX
#define TEXTBOX
#include <SFML/Graphics.hpp>
class TextBox{
    private:
        sf::Text* text;
        sf::RectangleShape* shape;
        sf::Texture* faceSprite;
        
    public:
        TextBox(sf::Texture* faceSprite, sf::RectangleShape* textBox, sf::Text* text);
};

#endif