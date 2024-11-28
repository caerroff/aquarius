#include "../include/Dialogue.hpp"
#include <iostream>

Dialogue::Dialogue()
{
  this->content = new sf::Text();
  this->author = new sf::Text();
}

Dialogue::Dialogue(std::string _content) : Dialogue(_content, "???")
{
  std::cout << "Called" << std::endl;
}

sf::RectangleShape *Dialogue::_createDialogueBox()
{
  sf::RectangleShape *box = new sf::RectangleShape(sf::Vector2f(1260, 150));
  box->setOutlineColor(sf::Color::White);
  box->setFillColor(sf::Color::Black);
  box->setOutlineThickness(2);
  box->setPosition(sf::Vector2f(10, 560));
  return box;
}

Dialogue::Dialogue(std::string _content, std::string _author)
{
  sf::Font *font = new sf::Font();
  font->loadFromFile("assets/font/PressStart2P-Regular.ttf");
  this->content = new sf::Text();
  this->author = new sf::Text();
  content->setString(_content);
  author->setString(_author);
  content->setFont(*font);
  author->setFont(*font);
  this->dialogueBox = this->_createDialogueBox();
  this->content->setCharacterSize(30);
  this->author->setCharacterSize(40);
  this->author->setColor(sf::Color::White);
  this->content->setColor(sf::Color::White);
  this->author->setPosition(this->dialogueBox->getPosition().x + 10, this->dialogueBox->getPosition().y + 10);
  this->content->setPosition(this->dialogueBox->getPosition().x + 150, this->dialogueBox->getPosition().y + 20);
}

void Dialogue::draw(sf::RenderWindow* window)
{
  window->draw(*this->dialogueBox);
  window->draw(*this->author);
  window->draw(*this->content);
}

