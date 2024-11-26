#ifndef MAP
#define MAP
#include <SFML/Graphics.hpp>
#include "Collidables/Character.hpp"
#include "Tile.hpp"
#include "Scene.hpp"
#include <vector>
#include <iostream>
#include <fstream>

class Map
{
    private:
        sf::Vector2f size;
        std::vector<Character*> characters;
        std::vector<Tile*> tiles;
        std::vector<Action*> actions;
        std::string musicPath;
        sf::Color* clearColor;
        Map* nextMap;
        const char* name;
    
    public:
        Map();
        Map(sf::Vector2f _size);
        sf::Vector2f getSize(){return this->size;}
        void setSize(sf::Vector2f _size){this->size = _size;}
        static Map* loadFromFile(char* _filePath);
        Map* loadFromAllMaps(char* _mapName);
        void update(sf::RenderWindow* window);
        void addCharacter(Character * character);
        void removeCharacterAt(int position);
        Character* getCharacterAt(int position);
        int getCharacterCount(){return this->characters.size();}
        void addTile(Tile* tile);
        void removeTileAt(int position);
        Tile* getTileAt(int position);
        const char* getName(){return this->name;}
        void setName(const char* _name){this->name = _name;}
        void setMusicPath(std::string _musicPath){this->musicPath = _musicPath;}
        std::string getMusicPath(){return this->musicPath;}
        void setClearColor(sf::Color* _clearColor){this->clearColor = _clearColor;}
        sf::Color* getClearColor(){return this->clearColor;}
        Action* getActionAt(int pos);
        void addAction(Action* action);
        int getActionCount(){return this->actions.size();}
};



#endif