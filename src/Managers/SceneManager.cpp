#include "SceneManager.hpp"


void SceneManager::update(sf::RenderWindow *window)
{
    window->clear(this->currentScene->getBgColor());
    for (int i = 0; i < currentScene->getNbTexts(); i++)
    {
        window->draw(*currentScene->getTextAt(i));
    }
    for (int i = 0; i < currentScene->getNbRectangles(); i++)
    {
        window->draw(*currentScene->getRectangleAtPosition(i));
    }

    if(this->getCurrentScene()->getMusic()->getStatus() == sf::SoundSource::Stopped)
    {
        this->stopModeScene();
    }
}

void SceneManager::loadScene(std::string path, sf::RenderWindow *window)
{
    this->window = window;
    currentScene = new Scene();
    currentScene->loadFromFile(path, window);
    currentScene->playMusic();
}

void SceneManager::stopModeScene()
{
    currentScene->stopMusic();
    currentMode = OFF_CODE;
}

void SceneManager::createCurrentScene()
{
    currentScene = new Scene();
}

int SceneManager::switchNextScene()
{
    this->getCurrentScene()->stopMusic();
    if(!currentScene->getNextSceneName().length() && !currentScene->getNextMapName().length())
    {
        return -1;
    }
    std::cout << "Scene name: " << currentScene->getNextSceneName() << std::endl;
    this->loadScene(currentScene->getNextSceneName(), this->window);
    return 0;
}