#include "../include/Button.hpp"

Button::Button(std::string _text, sf::Vector2f position, int margin, int size, std::string _font = "assets/font/PressStart2P-Regular.ttf")
{
    sf::Text *text = new sf::Text();
    sf::Font *font = new sf::Font();
    sf::RectangleShape *bg = new sf::RectangleShape();
    font->loadFromFile(_font);
    text->setFont(*font);
    text->setString(_text);
    text->setCharacterSize(size);
    text->setPosition(position);
    text->setFillColor(sf::Color::White);
    text->setOutlineColor(sf::Color::Black);
    text->setOutlineThickness(2);

    bg->setPosition(text->getPosition().x - margin, text->getPosition().y - margin);
    bg->setSize(sf::Vector2f(text->getLocalBounds().getSize().x + 2*margin, text->getLocalBounds().getSize().y + 2*margin));
    bg->setFillColor(sf::Color::Blue);
}