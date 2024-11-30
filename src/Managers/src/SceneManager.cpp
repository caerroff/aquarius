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
          this->switchNextScene();
          break;
        }
        if (currentDialogue < currentScene->getDialogues().size())
        {
          if (readyForNextDialogue)
          {
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
    if (readyForNextDialogue)
    {
      currentScene->getDialogues().at(currentDialogue)->drawEntirely(window);
    }
  }
}

void SceneManager::loadScene(std::string path, sf::RenderWindow *window)
{
  this->window = window;
  this->clock.restart();
  this->currentDialogue = 0;
  if (currentScene)
  {
    std::cout << "Freed scene: " << currentScene->getName() << std::endl;
    currentScene->destroy();
  }
  currentScene = new Scene();
  currentScene->loadFromFile(path, window);
  currentScene->getMusic()->setLoop(true);
  if (currentScene->getMusicPath().length() >= 1)
  {
    if (this->globalMusic)
    {
      std::cout << "Freed global music" << std::endl;
      this->globalMusic->stop();
      while (this->globalMusic->getStatus() != sf::Music::Status::Stopped)
      {
        ;
      }
      free(this->globalMusic);
    }
    currentScene->playMusic();
  }
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
  if (this->getCurrentScene()->getIsStopMusic())
  {
    this->getCurrentScene()->stopMusic();
  }
  else
  {
    this->globalMusic = currentScene->getMusic();
  }

  // If there is nothing next, return -1
  if (!currentScene->getNextSceneName().length() && !currentScene->getNextMapName().length())
  {
    return -1;
  }

  // Switching to GameplayMode if there is a map, to the next scene otherwise
  if (currentScene->getNextMapName().length())
  {
    this->stopModeScene();
    GameplayManager::getGameplayManager().setModeGameplay();
    GameplayManager::getGameplayManager().loadMap(this->currentScene->getNextMapName());
  }
  else
  {
    this->loadScene(this->getCurrentScene()->getNextSceneName(), window);
  }
  return 0;
}