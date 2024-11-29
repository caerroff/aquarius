#include "../include/SceneManager.hpp"

void SceneManager::update(sf::RenderWindow *window)
{
    sf::Event e;
    while (window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            this->stopModeScene();
            window->close();
            break;
        }
        if (e.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (currentDialogue >= currentScene->getDialogues().size())
                {
                    std::cout << "Next scene" << std::endl;
                    this->switchNextScene();
                    break;
                }
                if (currentDialogue < currentScene->getDialogues().size())
                {
                    if (readyForNextDialogue)
                    {
                        std::cout << "Switching Dialogue" << std::endl;
                        readyForNextDialogue = false;
                        currentDialogue++;
                    }
                    else
                    {
                        this->currentScene->getDialogues().at(currentDialogue)->drawEntirely(window);
                    }
                }
            }
        }
    }

    window->clear(this->currentScene->getBgColor());
    for (int i = 0; i < currentScene->getNbTexts(); i++)
    {
        window->draw(*currentScene->getTextAt(i));
    }
    for (int i = 0; i < currentScene->getNbRectangles(); i++)
    {
        window->draw(*currentScene->getRectangleAtPosition(i));
    }
    if (currentScene->getDialogues().size() && currentDialogue < currentScene->getDialogues().size())
    {
        if (currentScene->getDialogues().at(currentDialogue)->draw(window, &clock))
        {
            readyForNextDialogue = true;
        }
        if(readyForNextDialogue){
            currentScene->getDialogues().at(currentDialogue)->drawEntirely(window);
        }
    }

    if (this->getCurrentScene()->getMusic()->getStatus() == sf::SoundSource::Stopped)
    {
        this->stopModeScene();
    }
}

void SceneManager::loadScene(std::string path, sf::RenderWindow *window)
{
    this->window = window;
    this->clock.restart();
    this->currentDialogue = 0;
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
    if (!currentScene->getNextSceneName().length() && !currentScene->getNextMapName().length())
    {
        return -1;
    }
    std::cout << "Scene name: " << currentScene->getNextSceneName() << std::endl;
    this->loadScene(currentScene->getNextSceneName(), this->window);
    return 0;
}