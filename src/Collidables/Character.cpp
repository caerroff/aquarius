#include "Character.hpp"

Character::Character()
{
    this->name = "";
    this->body = new sf::RectangleShape();
}

Character::Character(char *_name)
{
    this->name = _name;
    this->body = new sf::RectangleShape();
}

Character::Character(char *_name, char *_spritePath)
{
    this->name = _name;
    this->spritePath = _spritePath;
}

void Character::update(sf::RenderWindow* window)
{
    window->draw(*this->body);
}

void Character::setFaceSprite(const char* _faceSpritePath)
{
    this->faceSprite = new sf::Texture();
    this->faceSprite->loadFromFile(_faceSpritePath);
}

void Character::setSprites(const char* _spritesPath)
{
    this->sprites = (sf::Texture**)calloc(6, sizeof(sf::Texture*));
    int posX = 0;
    int posY = 0;
    for(int i = 0; i < 6; i++)
    {
        this->sprites[i] = new sf::Texture();
        this->sprites[i]->loadFromFile(std::string(DEFAULT_SPRITE_PATH) + std::string(_spritesPath), sf::IntRect(sf::Vector2i(posX, posY), sf::Vector2i(32, 32)));
        if(i % 2 == 0){
            posX += 32;
        }
        else{
            posY += 32;
            posX = 0;
        }
    }
}

sf::RectangleShape* Character::getBody()
{
    return this->body;
}

void Character::setBody(sf::RectangleShape* body)
{
    this->body = body;
}

