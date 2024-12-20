#ifndef SCENE
#define SCENE
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include "../../UI/include/UI.hpp"
#include "Action.hpp"
#define DEFAULT_SCENE_PATH "assets/scene/"
#define DEFAULT_MUSIC_PATH "assets/music/"
#define DEFAULT_SOUND_PATH "assets/sound/"
#define DEFAULT_PORTRAIT_PATH "assets/portrait/"

class Scene
{
private:
  std::string name;
  sf::Music *music;
  sf::Color bgColor;
  std::string musicPath = "";
  std::vector<sf::Text *> sceneTexts;
  std::vector<sf::RectangleShape *> sceneRectangles;
  std::vector<Action *> sceneActions;
  std::vector<Dialogue *> dialogues;
  long numberOfFrames;
  long currentFrame;
  std::string nextScene;
  std::string nextMap;
  bool isStopMusic = true;

public:
  Scene();
  Scene(std::string name, std::string musicPath, int numberOfFrames);
  void setBgColor(sf::Color color) { this->bgColor = color; }
  void setName(std::string _name) { this->name = _name; }
  void setMusicPath(std::string _musicPath);
  std::string getMusicPath() { return this->musicPath; }
  std::string getName() { return this->name; }
  sf::Color getBgColor() { return this->bgColor; }
  void addText(std::string text, int x, int y, int size, std::string fontPath);
  std::vector<sf::Text *> getTexts() { return this->sceneTexts; }
  int getNbTexts() { return this->sceneTexts.size(); }
  sf::Text *getTextAt(int pos) { return this->sceneTexts.at(pos); }
  void addTextCenter(sf::RenderWindow *window, std::string _string, int size, int r, int g, int b, std::string fontPath);
  void addTextCenterWithY(sf::RenderWindow *window, std::string _string, int size, int y, int r, int g, int b, std::string fontPath);
  void addRectangle(sf::RectangleShape *rectangle) { sceneRectangles.push_back(rectangle); }
  sf::RectangleShape *getRectangleAtPosition(int position) { return sceneRectangles.at(position); }
  int getNbRectangles() { return sceneRectangles.size(); }
  void playMusic();
  void stopMusic();
  sf::Music *getMusic() { return this->music; }
  void update(sf::RenderWindow *window);
  void changeOpacityText(int position, int opacity);

  void loadFromFile(std::string path, sf::RenderWindow *window);

  void destroy();

  bool getIsStopMusic() { return this->isStopMusic; }

  std::string getNextSceneName() { return this->nextScene; }
  std::string getNextMapName() { return this->nextMap; }

  std::vector<Dialogue *> getDialogues() { return this->dialogues ;}
};

/**
 * Loads a dialogue from a YAML Node
 * @param node the node containing the dialogue
 * @return a pointer to the created dialogue
 */
Dialogue *loadDialogueFromNode(YAML::Node node);

#endif