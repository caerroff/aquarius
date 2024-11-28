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
  /**
   * Default constructor, everything empty.
   */
  Dialogue();

  /**
   * Constructor for the Dialogue class
   * @param content The content of the Dialogue
   */
  Dialogue(std::string content);

  /**
   * Constructor for the Dialogue class
   * @param content The content of the Dialogue
   * @param author The author of the Dialogue
   */
  Dialogue(std::string content, std::string author);

  void draw(sf::RenderWindow* window);
};

#endif