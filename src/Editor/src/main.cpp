#include <SFML/Graphics.hpp>
#include "../Managers/include/Managers.hpp"
#include <iostream>

int main(void)
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Editor");
    sf::RenderWindow *toolBox = new sf::RenderWindow(sf::VideoMode(500, 800), "Toolbox");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(true);
    window->setKeyRepeatEnabled(true);
    GameplayManager::getGameplayManager().setModeGameplay(window);
    GameplayManager::getGameplayManager().loadMap("firstMap.yaml", window);
    window->setTitle("Editor - firstMap.yaml");

    toolBox->setView(toolBox->getDefaultView());

    sf::Text *text = new sf::Text();
    text->setPosition(10, 100);
    text->setCharacterSize(25);
    text->setFillColor(sf::Color::Black);
    text->setOutlineColor(sf::Color::Black);
    text->setOutlineThickness(2);
    text->setString("");

    sf::Font *font = new sf::Font();
    font->loadFromFile("assets/font/PressStart2P-Regular.ttf");

    while (window->isOpen())
    {
        toolBox->clear(sf::Color::White);
        text->setString("hello world");
        GameplayManager::getGameplayManager().update(window);
        sf::Event e;
        while (toolBox->pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                toolBox->close();
                window->close();
            }

            if (e.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "Mouse pressed at " + std::to_string(sf::Mouse::getPosition(*toolBox).x) << std::endl;
                text->setString("Mouse pressed at " + std::to_string(sf::Mouse::getPosition(*toolBox).x));
            }
        }
        toolBox->draw(*text);
        // for (Tile *tile : GameplayManager::getGameplayManager().getTiles())
        // {
        //     sf::Text *text = new sf::Text();
        //     text->setString("std::to_string(tile->getId())");
        //     text->setPosition(100, 100);
        //     text->setCharacterSize(15);
        //     text->setFillColor(sf::Color::Black);
        //     toolBox->draw(*text);
        //     free(text);
        // }
        window->display();
        toolBox->display();
    }
    toolBox->close();
    return 0;
}