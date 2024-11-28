#include "Dialogue.hpp"

Dialogue::Dialogue(std::string _content)
{
  sf::Font *font = new sf::Font();
  font->loadFromFile("assets/font/PressStart2P-Regular.ttf");
  this->content = new sf::Text();
  this->author = new sf::Text();
  content->setString(_content);
  author->setString("???");
  content->setFont(*font);
  author->setFont(*font);
  this->dialogueBox = this->_createDialogueBox();
  this->content->setCharacterSize(30);
  this->author->setCharacterSize(40);
  this->author->setColor(sf::Color::White);
  this->content->setColor(sf::Color::White);
}

sf::RectangleShape *Dialogue::_createDialogueBox()
{
  sf::RectangleShape *box = new sf::RectangleShape(sf::Vector2f(1260, 150));
  box->setOutlineColor(sf::Color::White);
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
}


Dialogue *loadDialogueFromNode(YAML::Node node)
{
  std::string content = node["content"].as<std::string>();
  Dialogue *dialogue = (Dialogue *)malloc(sizeof(Dialogue));
  if (node["author"].IsDefined() && !node["author"].IsNull())
  {
    std::string author = node["author"].as<std::string>();
    dialogue = new Dialogue(content, author);
  }
  else
  {
    dialogue = new Dialogue(content);
  }
  return dialogue;
}

