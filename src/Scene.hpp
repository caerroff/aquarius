#ifndef SCENE
#define SCENE
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Action.cpp"
#define DEFAULT_SCENE_PATH "assets/scene/"
#define DEFAULT_MUSIC_PATH "assets/music/"

class Scene
{
private:
    char *name;
    sf::Music music;
    char *musicPath;
    std::vector<sf::Text *> sceneTexts;
    std::vector<sf::RectangleShape *> sceneRectangles;
    std::vector<Action *> sceneActions;
    long numberOfFrames;
    long currentFrame;

public:
    Scene();
    Scene(char *name, char *musicPath, int numberOfFrames);
    void setMusicPath(char *_musicPath);
    char* getMusicPath() { return this->musicPath; }
    void addText(char *text, int x, int y, int size, char *fontPath);
    std::vector<sf::Text *> getTexts() { return this->sceneTexts; }
    int getNbTexts() { return this->sceneTexts.size(); }
    sf::Text *getTextAt(int pos) { return this->sceneTexts.at(pos); }
    void addTextCenter(sf::RenderWindow *window, char *_string, int size, char *fontPath);
    void addRectangle(sf::RectangleShape *rectangle) { sceneRectangles.push_back(rectangle); }
    sf::RectangleShape *getRectangleAtPosition(int position) { return sceneRectangles.at(position); }
    int getNbRectangles() { return sceneRectangles.size(); }
    void playMusic();
    void stopMusic();
    sf::Music *getMusic() { return &this->music; }
    void update(sf::RenderWindow *window);
    void changeOpacityText(int position, int opacity);

    void loadFromFile(char *path, sf::RenderWindow* window);
};

#endif