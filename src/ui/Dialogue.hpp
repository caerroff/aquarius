#ifndef DIALOGUE
#define DIALOGUE
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <iostream>

class Dialogue
{
private:
  sf::RectangleShape *dialogueBox;
  sf::Text *content;
  sf::Text *author;
  sf::RectangleShape *_createDialogueBox();

public:
  Dialogue(YAML::Node node);
  Dialogue(std::string content);
  Dialogue(std::string content, std::string author);
};

#endif