#ifndef DIALOGUE
#define DIALOGUE
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <string>

class Dialogue
{
private:
  sf::RectangleShape *dialogueBox;
  sf::Text *content;
  sf::Text *author;
  sf::RectangleShape *_createDialogueBox();

public:
  Dialogue(std::string content);
  Dialogue(std::string content, std::string author);
};


/**
 * Loads a dialogue from a YAML Node
 * @param node the node containing the dialogue
 * @return a pointer to the created dialogue
 */
Dialogue *loadDialogueFromNode(YAML::Node node);

#endif