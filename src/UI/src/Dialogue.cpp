#include "../include/Dialogue.hpp"
#include <iostream>

Dialogue::Dialogue()
{
  sf::Font *font = new sf::Font();
  font->loadFromFile("assets/font/PressStart2P-Regular.ttf");
  this->drawnContent = new sf::Text();
  this->drawnContent->setString("");
  this->author = new sf::Text();
  this->music->setVolume(60);
  author->setString("");
  drawnContent->setFont(*font);
  drawnContent->setLineSpacing(1.25);
  author->setFont(*font);
  this->dialogueBox = this->_createDialogueBox();
  this->drawnContent->setCharacterSize(25);
  this->author->setCharacterSize(20);
  this->author->setColor(sf::Color::White);
  this->drawnContent->setColor(sf::Color::White);
  this->author->setPosition(this->dialogueBox->getPosition().x + 10, this->dialogueBox->getPosition().y + 15);
  this->drawnContent->setPosition(this->dialogueBox->getPosition().x + 50, this->dialogueBox->getPosition().y + 10);
}

Dialogue::Dialogue(std::string _content) : Dialogue()
{
  content = _content;
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

Dialogue::Dialogue(std::string _content, std::string _author) : Dialogue(_content)
{
  author->setString(_author);
  if (_author.length() > 1)
  {
    this->drawnContent->setPosition(this->dialogueBox->getPosition().x + 150, this->dialogueBox->getPosition().y + 10);
  }
}

Dialogue::Dialogue(std::string _content, std::string _author, std::string _music) : Dialogue(_content, _author)
{
  this->music->openFromFile(_music);
  this->isMusicInit = true;
}

void Dialogue::setPortrait(std::string path)
{
  this->portraitPath = path;
  this->portrait = new sf::RectangleShape(sf::Vector2f(100, 100));
  this->portrait->setPosition(this->dialogueBox->getPosition().x + 10, this->dialogueBox->getPosition().y + 45);
  this->portrait->setScale(0.9, 0.9);

  sf::Texture *texture = new sf::Texture();
  texture->loadFromFile(path);
  this->portrait->setTexture(texture);
}

int Dialogue::draw(sf::RenderWindow *window, sf::Clock *clock)
{
  window->draw(*this->dialogueBox);
  if (this->author->getString().getSize() > 1)
  {
    window->draw(*this->author);
  }

  if (this->portraitPath.length() > 1)
  {
    window->draw(*this->portrait);
  }
  window->draw(*this->drawnContent);
  if (drawnContent->getString().getSize() == content.length())
  {
    return 1;
  }
  if (clock->getElapsedTime().asMilliseconds() > 50)
  {

    this->drawnContent->setString(this->content.substr(0, this->drawnContent->getString().getSize() + 1));
    if (isMusicInit)
    {
      char drawnChar = this->content.at(this->drawnContent->getString().getSize() - 1);
      if (drawnChar != ' ' && drawnChar != '\n' && drawnChar != '!' && drawnChar != '.')
      {
        this->music->play();
      }
    }
    clock->restart();
  }
  return 0;
}

int Dialogue::drawEntirely(sf::RenderWindow *window)
{
  if (drawnContent->getString().getSize() != content.length())
  {
    drawnContent->setString(content);
  }
  window->draw(*this->dialogueBox);
  window->draw(*this->author);
  window->draw(*this->drawnContent);
  if (this->portraitPath.length() > 1)
  {
    window->draw(*this->portrait);
  }
  return 1;
}
