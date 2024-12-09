#include "../include/Character.hpp"

Character::Character()
{
    this->name = "";
    this->body = new sf::RectangleShape(sf::Vector2f(64, 64));
    this->body->setFillColor(sf::Color::White);
    this->body->setOrigin(sf::Vector2f(32, 32));
}

Character::Character(std::string _name) : Character()
{
    this->name = _name;
}

Character::Character(std::string _name, std::string _spritePath) : Character(_name)
{
    this->spritePath = _spritePath;
}

void Character::update(sf::RenderWindow *window)
{
    this->animate();
    this->setAnimation();
    if(this->currentState == State::TALKING)
    {
        this->currentDialogue->draw(window, &dialogueClock);
    }
    window->draw(*this->body);
}

void Character::setFaceSprite(std::string _faceSpritePath)
{
    this->faceSprite = new sf::Texture();
    this->faceSprite->loadFromFile(_faceSpritePath);
}

sf::RectangleShape *Character::getBody()
{
    return this->body;
}

void Character::setBody(sf::RectangleShape *body)
{
    this->body = body;
}

void Character::loadSprite(std::string path, sf::Vector2i size)
{
    this->spriteSheet = new sf::Texture();
    this->spriteSheet->loadFromFile(DEFAULT_CHARACTER_SPRITE_PATH + path);
    this->body->setTexture(spriteSheet);
    this->body->setFillColor(sf::Color::White);
    this->body->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
    this->updateSpriteInfos();
    animationClock.restart();
}

void Character::animate()
{
    if(animationInfos.lastRow != animationInfos.currentRow)
    {
        animationInfos.currentColumn = 0;
    }
    animationInfos.lastRow = animationInfos.currentRow;
    if (velocity.x == 0 && velocity.y == 0)
    {
        animationInfos.currentRow = 0;
        return;
    }
    if (this->velocity.x < 0)
    {
        animationInfos.currentRow = 1;
        body->setScale(1.0f, 1.0f);
        return;
    }
    else if (this->velocity.x > 0)
    {
        animationInfos.currentRow = 1;
        body->setScale(-1.0f, 1.0f);
        return;
    }

    if (this->velocity.y > 0)
    {
        animationInfos.currentRow = 3;
        return;
        // Turn the sprite up;
    }
    else if (this->velocity.y < 0)
    {
        animationInfos.currentRow = 2;
        return;
        // Turn the sprite down;
    }
}

void Character::setAnimation()
{
    if (animationInfos.currentColumn <= animationInfos.nbSpritesPerRow[animationInfos.currentRow] && animationClock.getElapsedTime().asMilliseconds() > 100)
    {
        animationClock.restart();
        sf::IntRect intRect = body->getTextureRect();
        // body->setTextureRect(sf::IntRect(sf::Vector2i(animationInfos.currentColumn * intRect.width, intRect.top), sf::Vector2i(intRect.width, intRect.height)));
        body->setTextureRect(sf::IntRect(animationInfos.currentColumn * intRect.width, animationInfos.currentRow * intRect.height, intRect.width, intRect.height));
        if (animationInfos.currentColumn + 1 < animationInfos.nbSpritesPerRow[animationInfos.currentRow])
        {
            animationInfos.currentColumn++;
        }
        else
        {
            animationInfos.currentColumn = 0;
        }
    }
}

void Character::updateSpriteInfos()
{
    // Read the entire texture
    sf::Vector2u size = this->spriteSheet->getSize();

    int row;
    int col;
    // Make a IntRect that goes through the whole sheet
    sf::Image image = spriteSheet->copyToImage();
    bool spriteDetected = false;
    // this->animationInfos.nbSpritesPerRow = (int *)calloc((int)size.y / body->getTextureRect().height, sizeof(int));
    this->animationInfos.nbSpritesPerRow = (int *)malloc(((int)size.y / body->getTextureRect().height) * sizeof(int));

    // For every row in the spriteSheet
    for (int y = 0; y < size.y; y += body->getTextureRect().height)
    {
        animationInfos.nbSpritesPerRow[animationInfos.rowNb] = 0;
        animationInfos.rowNb++;
        row = y;
        // For every column in the sprite sheet
        for (int x = 0; x < size.x; x += body->getTextureRect().width)
        {
            col = x;
            // Go through the whole IntRect
            spriteDetected = false;
            for (int i = 0; i < body->getTextureRect().width; i++)
            {
                for (int j = 0; j < body->getTextureRect().height && !spriteDetected; j++)
                {
                    // if there is any colour in this sprite
                    if (image.getPixel(x + i, y + j) != sf::Color::Transparent)
                    {
                        // I know it exists

                        spriteDetected = true;
                        this->animationInfos.nbSpritesPerRow[(int)y / 64]++;
                        break;
                    }
                }
            }
            if (!spriteDetected)
                break;
        }
    }
}

void Character::dialogue(sf::RenderWindow *window)
{
    this->currentState = State::TALKING;
    this->dialogueClock.restart();
    this->currentDialogue = new Dialogue("Hi Everyone...", this->name);
}