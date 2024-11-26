#ifndef JSON
#define JSON
#include <iostream>
#include <fstream>
#include "../Map.hpp"
#include "../Collidables/Character.hpp"
#include "../Tile.hpp"
#include "../Action.hpp"
#include "map"

#define DEFAULT_MAP_PATH "assets/maps/"

Map* loadJsonMap(char* _filePath);
std::map<std::string, std::string> parseJson(std::string json);
Character* loadJsonCharacter(std::string json);
Tile* loadJsonTile(std::string json);
Action* loadJsonAction(std::string json);
std::string getNextJsonObject(std::string fullJson, int currentPos);


#endif