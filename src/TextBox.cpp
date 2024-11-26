#include "TextBox.hpp"

TextBox::TextBox(sf::Texture* faceSprite, sf::RectangleShape* textBox, sf::Text* text)
{
    this->faceSprite = faceSprite;
    this->shape = textBox;
    this->text = text;
}