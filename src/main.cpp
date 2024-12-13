#include <iostream>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collidables/include/Collidables.hpp"
#include <yaml-cpp/yaml.h>
#include "Managers/include/Managers.hpp"

void handleKeys(sf::RenderWindow *window);

std::array<bool, sf::Keyboard::KeyCount> keyState;

int main(void)
{
    keyState.fill(false);
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Aquarius", sf::Style::Titlebar | sf::Style::Close);
    sf::Image *icon = new sf::Image();
    icon->loadFromFile("assets/icon.png");

    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(false);
    window->setKeyRepeatEnabled(true);
    if (icon->getSize().x)
    {
        window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
    }

    SceneManager::getSceneManager().setModeScene(window);
    SceneManager::getSceneManager().loadScene("opening.yaml", window);
    while (window->isOpen())
    {
        handleKeys(window);
        window->clear(sf::Color::Black);
        if (SceneManager::getSceneManager().getCurrentMode() == SCENE_CODE)
        {
            SceneManager::getSceneManager().update(window);
        }
        else if (GameplayManager::getGameplayManager().getCurrentMode() == GAMEPLAY_CODE)
        {
            GameplayManager::getGameplayManager().update(window);
        }
        else
        {
            std::cout << SceneManager::getSceneManager().getCurrentMode() << std::endl;
            fprintf(stderr, "Warning ! Thrown to GameplayMode because no mode was set\n");
            GameplayManager::getGameplayManager().setModeGameplay(window);
            GameplayManager::getGameplayManager().update(window);
        }
        window->display();
    }
    return 0;
}

void handleKeys(sf::RenderWindow *window)
{
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        keyState[sf::Keyboard::R] = false;
    }

    if (!keyState[sf::Keyboard::R] && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        keyState[sf::Keyboard::R] = true;
        if (window->getSize().x == 1280)
        {
            window->setSize(sf::Vector2u(1600, 900));
        }
        else if (window->getSize().x == 1600)
        {
            window->setSize(sf::Vector2u(1920, 1080));
        }
        else
        {
            window->setSize(sf::Vector2u(1280, 720));
        }
        return;
    }
}