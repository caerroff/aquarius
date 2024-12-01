#ifndef SCENEMANAGER
#define SCENEMANAGER
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scene.hpp"
#include <SFML/Main.hpp>
#include "../include/GameplayManager.hpp"
#include <chrono>
#define SCENE_CODE 1
#define OFF_CODE 2

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
    sf::RenderWindow *window = (sf::RenderWindow *)malloc(sizeof(sf::RenderWindow));
    int currentMode;
    sf::Clock clock;
    int currentDialogue = 0;
    bool readyForNextDialogue = false;
    sf::Music *globalMusic;

protected:
    static SceneManager *singleton_;

public:
    SceneManager(SceneManager const &) = delete;
    void operator=(SceneManager const &) = delete;
    Scene *getCurrentScene() { return this->currentScene; }
    void setModeScene(sf::RenderWindow *window);
    void stopModeScene();
    int getCurrentMode() { return currentMode; }
    void update(sf::RenderWindow *window);

    
    void loadScene(std::string path, sf::RenderWindow *window);
    void createCurrentScene();
    
    /**
     * Skips to the next scene.
     * @param path the path to the scene file
     * @param window the window to render the scene to
     * @return `0` if there is a next scene, `-1` otherwise
     */
    int switchNextScene();
};

#endif