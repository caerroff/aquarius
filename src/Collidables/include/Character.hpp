#ifndef CHARACTER
#define CHARACTER
#define DEFAULT_SPRITE_PATH "assets/sprites/"
#define DEFAULT_CHARACTER_SPRITE_PATH "assets/sprites/Characters/"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "CollisionEntity.hpp"
#include "Animation.hpp"

class Character : public CollisionEntity
{
private:
    std::string name;
    std::string spritePath;
    sf::RectangleShape* body;
    sf::RectangleShape* head;
    sf::RectangleShape* hitbox;
    sf::Texture* faceSprite;
    sf::Texture* spriteSheet;

protected:
    sf::Vector2f velocity;
    Animation animation = Animation();

public:
    Character();
    Character(std::string name);
    Character(std::string name, std::string spritePath);
    std::string getName() { return this->name; }
    void setName(std::string _name) { this->name = _name; }
    sf::Texture* getFaceSprite(){return this->faceSprite;}
    sf::Texture* getSpriteSheet(){return this->spriteSheet;}
    void setFaceSprite(std::string _faceSpritePath);
    void update(sf::RenderWindow* window);
    void loadSprite(std::string path, sf::Vector2i size = sf::Vector2i(64, 64));
    sf::RectangleShape* getBody();
    void setBody(sf::RectangleShape* body);

    void setPosition(sf::Vector2f position) { this->body->setPosition(position) ;}
    sf::Vector2f getPosition() { return this->body->getPosition();}

    sf::Vector2f getVelocity() { return this->velocity ;}
};

#endif