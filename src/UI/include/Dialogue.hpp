#ifndef DIALOGUE
#define DIALOGUE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <yaml-cpp/yaml.h>
#include <string>
#include <chrono>

class Dialogue
{
private:
  sf::RectangleShape *dialogueBox;
  sf::Text *drawnContent;
  std::string content;
  sf::Music *music = new sf::Music();
  sf::Text *author;
  sf::RectangleShape *_createDialogueBox();
  bool isMusicInit = false;
  sf::RectangleShape *portrait;
  std::string portraitPath;

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

  Dialogue(std::string content, std::string author, std::string soundPath);

  std::string getAuthor() {return this->author->getString();}

  void setPortrait(std::string path);

  int draw(sf::RenderWindow* window, sf::Clock *clock);
  int drawEntirely(sf::RenderWindow* window);
};

#endif