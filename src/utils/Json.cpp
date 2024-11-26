#include "Json.hpp"

Map *loadJsonMap(char *_filePath)
{
    std::cout << "Loading map from " << DEFAULT_MAP_PATH << _filePath << std::endl;
    Map* map = new Map();
    std::ifstream file(std::string(DEFAULT_MAP_PATH) + std::string(_filePath));
    std::string line;
    std::string json;
    while (std::getline(file, line))
    {
        json += line;
        for(int i = 0; i < line.length(); i++)
        {
            std::string key;
            std::string value;
            if(line[i] == '"')
            {
                
                i++;
                while(line[i] != '"')
                {
                    key += line[i];
                    i++;
                }
                if(key == "")
                {
                    continue;
                }
                std::cout << "Key : " << key << std::endl;
                if(key == "Name")
                {
                    value = line.substr(i+3, line.length() - i - 5);
                    map->setName(value.c_str());
                }

                if(key == "Music")
                {
                    value = line.substr(i+3, line.length() - i - 5);
                    map->setMusicPath(value);
                }
                if(key == "Background")
                {
                    value = line.substr(i+3, line.length() - i - 5);
                    int r = std::stoi(value.substr(0, value.find(",")));
                    value = value.substr(value.find(",") + 1, value.length() - value.find(",") - 1);
                    int g = std::stoi(value.substr(0, value.find(",")));
                    value = value.substr(value.find(",") + 1, value.length() - value.find(",") - 1);
                    int b = std::stoi(value.substr(0, value.find(",")));    
                    std::cout << "R : " << r << std::endl;
                    std::cout << "G : " << g << std::endl;
                    std::cout << "B : " << b << std::endl;
                    sf::Color* color = new sf::Color(r, g, b);       
                    map->setClearColor(color);
                    continue;
                }
                if(key == "Actions")
                {
                    std::cout << "Got JSON : " << getNextJsonObject(json, i) << std::endl;
                    Action* action = loadJsonAction(getNextJsonObject(json, i));
                    map->addAction(action);
                }
                if(key == "Tiles")
                {
                    Tile* tile = loadJsonTile(value);
                    map->addTile(tile);
                }
                if(key == "Characters")
                {
                    Character* character = loadJsonCharacter(value);
                    map->addCharacter(character);
                }


                std::cout << "Value : " << value << std::endl;
                continue;
            }
            continue;
        }
    }
    file.close();
    if(json == "")
    {
        std::cout << "Error while loading the map" << std::endl;
        return map;
    }

    std::cout << "Done loading the map" << std::endl;
    return map;
}

std::map<std::string, std::string> parseJson(std::string json)
{
    std::map<std::string, std::string> parse;
    std::string key;
    std::string value;
    
    std::string actualJson = json.substr(1, json.length() - 2);

    std::string subString;
    std::cout << "Parsing length " << actualJson.length() << std::endl;
    for(int i = 0 ; i < actualJson.length(); i++)
    {
        key = "";
        value = "";
        std::cout << "Parsing " << actualJson[i] << std::endl;
        while(actualJson[i] != ':')
        {
            key += actualJson[i];
            i++;
        }
        if(actualJson[i] == '"')
        {
            i++;
            while(actualJson[i+1] != '"')
            {
                value += actualJson[i];
                i++;
            }
            std::cout << "Key :" << key << std::endl;
            std::cout << "Value :" << value << std::endl;
            parse[key] = value;
        }
    }

    for(std::map<std::string, std::string>::iterator i = parse.begin(); i != parse.end(); i++)
    {
        std::cout << "Key :" << i->first << std::endl; 
        std::cout << "Value :" << i->second << std::endl;
    }

    return parse;
}

Action* loadJsonAction(std::string json)
{
    Action* action = new Action();
    action->setType(UNDEFINED);
    return new Action();
}

Tile* loadJsonTile(std::string json)
{
    return new Tile();
}

Character* loadJsonCharacter(std::string json)
{
    return new Character();
}

std::string getNextJsonObject(std::string fullJson, int currentPos){
    std::string jsonObject = "";

    while(fullJson[currentPos] != '{')
    {
        currentPos++;
        jsonObject += fullJson[currentPos];
    }
    currentPos++;
    int enteredBrace = 0;    
    do{
        if(fullJson[currentPos] == '{')
            enteredBrace ++;
        if(fullJson[currentPos] == '}')
            enteredBrace --;

        jsonObject += fullJson[currentPos];
        
        currentPos++;
    }while(enteredBrace != 0 && currentPos < fullJson.length());

    return jsonObject;
}