#include "../include/Character.hpp"

Character::Character()
{
    this->name = "";
    this->body = new sf::RectangleShape(sf::Vector2f(64, 64));
    this->body->setFillColor(sf::Color::White);
}

Character::Character(std::string _name) : Character()
{
    this->name = _name;
}

Character::Character(std::string _name, std::string _spritePath) : Character(_name)
{
    this->spritePath = _spritePath;
}

void Character::update(sf::RenderWindow* window)
{
    window->draw(*this->body);
}

void Character::setFaceSprite(std::string  _faceSpritePath)
{
    this->faceSprite = new sf::Texture();
    this->faceSprite->loadFromFile(_faceSpritePath);
}

sf::RectangleShape* Character::getBody()
{
    return this->body;
}

void Character::setBody(sf::RectangleShape* body)
{
    this->body = body;
}

void Character::loadSprite(std::string path, sf::Vector2i size)
{
    this->spriteSheet = new sf::Texture();
    this->spriteSheet->loadFromFile(DEFAULT_CHARACTER_SPRITE_PATH + path);
    this->body->setTexture(spriteSheet);
    this->body->setFillColor(sf::Color::White);
    this->body->setTextureRect(sf::IntRect(sf::Vector2i(0,0), size));
}