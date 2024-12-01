#ifndef GAMEPLAYMANAGER
#define GAMEPLAYMANAGER
#define GAMEPLAY_CODE 1
#define OFF_CODE 2
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "../../Collidables/include/Collidables.hpp"
#include "Map.hpp"
#include <SFML/Main.hpp>
#define TEXTBOX_WIDTH 1000
#define TEXTBOX_HEIGHT 200
#define TEXTBOX_X 140
#define TEXTBOX_Y 500

class GameplayManager
{
    private:
        GameplayManager() {}
        static GameplayManager *singleton_;
        int currentMode;
        sf::Music music;
        sf::Clock chrono;
        sf::Text *fpsCounter = new sf::Text();
        std::string musicPath;
        std::string nextMapPath = "";
        Map *map;
    
    public:
        static GameplayManager &getGameplayManager()
        {
            static GameplayManager instance;
            return instance;
        }
        GameplayManager(GameplayManager const &) = delete;
        void operator=(GameplayManager const &) = delete;
        void operator~() = delete;
        void setMusicPath(const char *_musicPath);
        std::string getMusicPath() { return this->musicPath; }
        void playMusic();
        void stopMusic();
        void setModeGameplay();
        void stopModeGameplay();
        void addCharacter();
        void addTile(Tile* tile);
        void characterTextBox(int characterIndex, char* text);
        void loadMap(std::string path);
        void removeCharacterAt(int position);
        int getCurrentMode();
        void update(sf::RenderWindow* window);
        int switchNextMap();
};


#endif