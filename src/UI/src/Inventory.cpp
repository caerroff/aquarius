#include "../include/Inventory.hpp"

Inventory::Inventory(sf::RenderWindow *window)
{
    this->window = window;
    this->_createVirtualWindow(window);
    this->font = new sf::Font();
    font->loadFromFile("assets/font/PressStart2P-Regular.ttf");
    this->selector = new sf::ConvexShape();
    selector->setPointCount(3);
    selector->setPoint(0, sf::Vector2f(0, 0));
    selector->setPoint(1, sf::Vector2f(20, 10));
    selector->setPoint(2, sf::Vector2f(0, 20));
    selector->setFillColor(sf::Color::White);
    selector->setPosition(sf::Vector2f(virtualWindow->getPosition().x + 10, (virtualWindow->getPosition().y + 23 / 2) + 10));
}

Inventory::Inventory(Player *player, sf::RenderWindow *window) : Inventory(window)
{
    this->player = player;
}

void Inventory::_createVirtualWindow(sf::RenderWindow *window)
{
    this->virtualWindow = new sf::RectangleShape();
    this->virtualWindow->setSize(sf::Vector2f(500, 500));
    virtualWindow->setFillColor(sf::Color::Black);
    virtualWindow->setOutlineColor(sf::Color::White);
    virtualWindow->setOutlineThickness(2);
    this->virtualWindow->setPosition(sf::Vector2f((window->getView().getSize().x / 2) - (virtualWindow->getSize().x /2), (window->getView().getSize().y / 2) - (virtualWindow->getSize().y / 2)));
}

void Inventory::render()
{
    this->window->draw(*virtualWindow);
    for(auto text: texts)
    {
        this->window->draw(text);
    }
    this->window->draw(*selector);
}

void Inventory::update()
{
    texts.clear();
    int y_position = 0;
    for(auto item : player->getAllItems())
    {
        sf::Text text;
        text.setFont(*this->font);
        text.setString(item->getName());
        text.setCharacterSize(23);
        text.setPosition(sf::Vector2f(virtualWindow->getPosition().x + 40, virtualWindow->getPosition().y + 20 + y_position));
        texts.push_back(text);
        y_position += 40;
    }
}

