#ifndef SCENEMANAGER
#define SCENEMANAGER
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Scene.cpp"
#define SCENE_CODE 1
#define OFF_CODE 2

int currentMode;

class SceneManager
{
public:
    static SceneManager &getSceneManager()
    {
        static SceneManager instance;
        return instance;
    }

private:
    SceneManager() {}
    Scene *currentScene;
    Scene *nextScene;

protected:
    static SceneManager *singleton_;

public:
    SceneManager(SceneManager const &) = delete;
    void operator=(SceneManager const &) = delete;
    Scene *getCurrentScene() { return this->currentScene; }
    void setModeScene() { currentMode = SCENE_CODE; }
    void stopModeScene();
    int getCurrentMode() { return currentMode; }
    void update(sf::RenderWindow *window);
    void loadScene(char *path, sf::RenderWindow *window);
    void createCurrentScene();
    int switchNextScene();
};

#endif