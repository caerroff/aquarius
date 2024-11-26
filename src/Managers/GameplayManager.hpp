#ifndef GAMEPLAYMANAGER
#define GAMEPLAYMANAGER
#define GAMEPLAY_CODE 1
#define OFF_CODE 2
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "vector"
#include "../Collidables/Player.hpp"
#include "../Tile.cpp"
#include "../TextBox.cpp"
#include "../Map.cpp"
#define DEFAULT_MUSIC_PATH "assets/music/"
#define DEFAULT_SPRITE_PATH "assets/sprites/"
#define DEFAULT_FONT_PATH "assets/fonts/PressStart2P-Regular.ttf"
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
        std::string musicPath;
        Map *map;
        TextBox* currentTextBox;
    
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
        void loadMap(char* _filePath);
        void loadDefaultMap(); // This should be deleted in the future
        void removeCharacterAt(int position);
        int getCurrentMode();
        void update(sf::RenderWindow* window);
        int switchNextMap();
};


#endif