#ifndef CHARACTER
#define CHARACTER
#define DEFAULT_SPRITE_PATH "assets/sprites/"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "CollisionEntity.hpp"

class Character : public CollisionEntity
{
private:
    const char *name;
    const char *spritePath;
    sf::RectangleShape* body;
    sf::RectangleShape* head;
    sf::RectangleShape* hitbox;
    sf::Texture* faceSprite;
    sf::Texture** sprites;

public:
    Character();
    Character(char *name);
    Character(char *name, char *spritePath);
    const char *getName() { return this->name; }
    void setName(const char *_name) { this->name = _name; }
    sf::Texture* getFaceSprite(){return this->faceSprite;}
    sf::Texture** getSprites(){return this->sprites;}
    void setFaceSprite(const char* _faceSpritePath);
    void setSprites(const char* _spritesPath);
    void loadFromFile(const char* _filePath);
    virtual void update(sf::RenderWindow* window);
    sf::RectangleShape* getBody();
    void setBody(sf::RectangleShape* body);
};

#endif