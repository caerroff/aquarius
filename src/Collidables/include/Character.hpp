#ifndef CHARACTER
#define CHARACTER
#define DEFAULT_SPRITE_PATH "assets/sprites/"
#define DEFAULT_CHARACTER_SPRITE_PATH "assets/sprites/Characters/"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "CollisionEntity.hpp"
#include <iostream>
#include "../../UI/include/Dialogue.hpp"

struct AnimationInfos
{
    int currentRow = 0;
    int currentColumn = 0;
    int lastRow = 0;
    int lastColumn = 0;
    int *nbSpritesPerRow = (int *)calloc(1, sizeof(int));
    int rowNb = 0;
};

enum State {
    AFK,
    TALKING,
};

class Character : public CollisionEntity
{
private:
    std::string name;
    sf::RectangleShape *head;
    sf::RectangleShape *hitbox;
    sf::Texture *faceSprite;

protected:
    std::string spritePath;
    sf::Clock animationClock = sf::Clock();
    sf::Clock dialogueClock = sf::Clock();
    AnimationInfos animationInfos = AnimationInfos();
    sf::Texture *spriteSheet;
    sf::Vector2f velocity;
    State currentState = State::AFK;
    Dialogue* currentDialogue = nullptr;

public:
    Character();
    Character(std::string name);
    Character(std::string name, std::string spritePath);
    std::string getName() { return this->name; }
    void setName(std::string _name) { this->name = _name; }
    sf::Texture *getFaceSprite() { return this->faceSprite; }
    sf::Texture *getSpriteSheet() { return this->spriteSheet; }
    void setFaceSprite(std::string _faceSpritePath);
    void update(sf::RenderWindow *window);
    void loadSprite(std::string path, sf::Vector2i size = sf::Vector2i(64, 64));
    sf::RectangleShape *getBody();
    void setBody(sf::RectangleShape *body);

    void setPosition(sf::Vector2f position) { this->body->setPosition(position); }
    sf::Vector2f getPosition() { return this->body->getPosition(); }

    sf::Vector2f getVelocity() { return this->velocity; }

    State getCurrentState() { return this->currentState ;}

    void setCurrentState(State state) {this->currentState = state;}

    /**
     * @brief starts the dialogue of the character and displays it on the window
     * @param window A pointer to the window we want to display the dialogue to.
     */
    void dialogue(sf::RenderWindow *window);

    void skipDialogue(){this->currentDialogue = nullptr; currentState = State::AFK;}

    /**
     * @brief Handles the animation of the Character
     * Flips the sprite if the Character is facing left
     * Changes Sprite row depending on actions.
     */
    void animate();

    /**
     * @brief After loading the sprite sheet, this function reads the sheet entirely
     * and stores the number of rows, the number of sprites per row and sets the current row to 0
     */
    void updateSpriteInfos();

    void setAnimation();
};

#endif