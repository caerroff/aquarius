#include <iostream>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collidables/Player.cpp"
#include "Save.cpp"
#include "yaml-cpp/yaml.h"
#include "Managers/SceneManager.cpp"
#include "Managers/GameplayManager.cpp"

void handleKeys(sf::Keyboard::Key key, sf::RenderWindow *window);

int main(void)
{
    try
    {
        YAML::Node node = YAML::LoadFile("assets/scene/opening.yaml");
        std::cout << node["Name"] << std::endl;
        std::cout << node["Texts"][0] << std::endl;
    }
    catch (YAML::BadFile e)
    {
        std::cerr << "Error: " << e.msg << std::endl;
    }
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Aquarius", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

    SceneManager::getSceneManager().setModeScene();
    SceneManager::getSceneManager().loadScene("opening.scene", window);
    while (window->isOpen())
    {
        sf::Event e;
        while (window->pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                SceneManager::getSceneManager().stopModeScene();
                window->close();
                break;
            }
            if (e.type == sf::Event::KeyPressed)
            {
                handleKeys(e.key.code, window);
            }
        }
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
            // FIX: Error when arriving here -> segmentation fault
            fprintf(stderr, "Warning ! Thrown to GameplayMode because no mode was set\n");
            GameplayManager::getGameplayManager().setModeGameplay();
            GameplayManager::getGameplayManager().update(window);
        }
        window->display();
    }
    return 0;
}

void handleKeys(sf::Keyboard::Key key, sf::RenderWindow *window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        if (window->getSize().x == 1280)
        {
            window->setSize(sf::Vector2u(1920, 1080));
        }
        else if (window->getSize().x == 1920)
        {
            window->setSize(sf::Vector2u(2400, 1350));
        }
        else
        {
            window->setSize(sf::Vector2u(1280, 720));
        }
        return;
    }
    if (key == sf::Keyboard::Space && SceneManager::getSceneManager().getCurrentMode() == SCENE_CODE)
    {
        if (!SceneManager::getSceneManager().switchNextScene() == 0)
        {
            SceneManager::getSceneManager().stopModeScene();
            GameplayManager::getGameplayManager().setModeGameplay();
            GameplayManager::getGameplayManager().loadDefaultMap();
        }
    }
}